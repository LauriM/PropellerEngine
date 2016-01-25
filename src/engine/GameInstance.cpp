// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/GameInstance.h"

#include "engine/sys/Sleep.h"
#include "engine/preprocessor/platform.h"
#include "engine/file/AndroidAssetManagerArchive.h"
#include "engine/PlatformInitialization.h"
#include "engine/sys/Timer.h"
#include "engine/renderer/CameraSystem.h"
#include "engine/sys/FileSystem.h"
#include "engine/resource/ResourceManager.h"
#include "engine/scene/Scene.h"
#include "engine/console/Cvar.h"
#include "engine/renderer/PropellerModelLoader.h"
#include "engine/console/IngameConsoleSystem.h"
#include "engine/console/Console.h"
#include "engine/physics/RigidBodyComponent.h"
#include "engine/component/Component.h"
#include "engine/file/FileManager.h"
#include "engine/file/DirectoryArchive.h"
#include "engine/lang/HandleManager.h"
#include "engine/stream/BufferedOutputStream.h"
#include "engine/stream/OutputStream.h"
#include "engine/stream/InputStream.h"
#include "engine/scene/Entity.h"
#include "engine/scene/TransformComponent.h"
#include "engine/renderer/TextureLoader.h"
#include "engine/scene/CameraComponent.h"
#include "engine/scene/EntityType.h"
#include "engine/sys/FileSystem.h"
#include "engine/input/KeyCodes.h"
#include "engine/file/PackageArchive.h"
#include "engine/GameMode.h"
#include "engine/profiler/ProfilerManager.h"
#include "engine/profiler/AutoProfiler.h"
#include "engine/input/AndroidInputSystem.h"
#include "engine/scene/SceneManager.h"
#include "engine/physics/Box2DPhysicSystem.h"
#include "engine/sys/Socket.h"
#include "engine/network/ServerSystem.h"
#include "engine/network/ClientSystem.h"

#include "engine/renderer/RendererSystem.h"
#include "engine/renderer/ShaderLoader.h"

#ifdef OS_ANDROID
#include <android_native_app_glue.h>
#endif

#ifndef GAMEINSTANCE_CVAR
#define GAMEINSTANCE_CVAR

namespace cvar {
	CVAR(int, developer, 0, true);
	CVAR(int, editor, 0, false);
	CVAR(int, dimensions, 2, false); //in how many dimensions the engine is set to run
	CVAR(int, dump_profiler_on_shutdown, 0, true);
	CVAR(int, worker_threads, 4, true);

	EXTERN_CVAR(String, defaultScene);
	EXTERN_CVAR(int, r_width);
	EXTERN_CVAR(int, r_height);
}

#endif

namespace command {

	CREATE_COMMAND(ls, "List files")
	{
		LOG_INFO("Filelist: ");

		engine::file::FileList list;
		instance->getFileManager()->listFiles(list);

		unsigned i;

		for (i = 0; i < list.getFiles().size(); ++i)
		{
			LOG_INFO("> " << list.getFiles()[i]);
		}

		LOG_INFO("Total of " << i << " files listed.");

		return 0;
	}

	CREATE_COMMAND(entitylist, "List entities in scenes")
	{
		const engine::scene::Scene::EntityList *list = instance->getScene()->getEntityList();

		for (unsigned i = 0; i < list->size(); ++i)
		{
			engine::scene::Entity *ent = list->at(i);

			LOG_INFO(" > " << ent->getName());

			engine::scene::Entity::ComponentList components = ent->getComponents();

			for (unsigned x = 0; x < components.size(); ++x)
			{
				engine::component::Component *comp = components[x];

				LOG_INFO("    - " << comp->getTypeInfo()->getTypeName());
			}
		}

		return 0;
	}

	CREATE_COMMAND(scene, "Load scene by name")
	{
		if (args->size() < 2)
		{
			LOG_WARNING("not enough parameters!");
			return -1;
		}

		instance->getSceneManager()->loadScene(args->at(1));

		/*
		if (*cvar::developer)
		{
			LOG_INFO("Developer mode enabled, loading scene from disk, not archive");
			instance->loadSceneFromDisk(args->at(1));
		}
		else
		{
			instance->loadSceneFromArchive(args->at(1));
		}
		*/

		return 0;
	}

	CREATE_COMMAND(quit, "Close the game")
	{
		instance->uninit();

		return 0;
	}
}

namespace engine {

	GameInstance::GameInstance()
		: accumulator(0.f)
		, t(0)
		, hibernating(false)
	{
		sys::initializeFilesystem();
		platformInitialization();
		sys::initNetworking();

		// Lets make sure the handlemanager is ready as soon as its required!
		context.handleManager = &handleManager;
		context.scheduler = &scheduler;

		console = new engine::console::Console(this);

		console->execute("exec config.cfg");

		// After exec config.cfg
		scheduler.init(*cvar::worker_threads);
	}

	//Init rendering, if hwnd given, specialize to it
	void GameInstance::initializeRenderer(intptr_t hwndIntptr)
	{
		PROFILE;

#if defined (OS_WINDOWS)
		hwnd = (HWND)hwndIntptr;
#endif

#ifdef _EDITOR
		*cvar::editor = true;

		RECT rect;
		GetWindowRect((HWND)hwnd, &rect);

		*cvar::r_width = rect.right - rect.left;
		*cvar::r_height = rect.bottom - rect.top;
#endif

#if defined (RENDERING_ENABLED)
		cameraSystem = new engine::renderer::CameraSystem(&inputSystem);
		rendererSystem = new engine::renderer::RendererSystem((void*)hwndIntptr, &resourceManager, cameraSystem);
#endif
	}

	void GameInstance::init()
	{
		PROFILE;
		LOG_INFO("Engine starting!");

		scene = new engine::scene::Scene(&context);

		if (*cvar::dimensions != 2 || *cvar::dimensions != 3)
		{
			LOG_ERROR("Invalid dimensions detected! Falling back to 3");
			*cvar::dimensions = 3;
		}

#ifdef OS_WINDOWS
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		LOG_INFO("Platform Windows");
		LOG_INFO("Processors: " << sysInfo.dwNumberOfProcessors);
		LOG_INFO("ProcessorType: " << sysInfo.dwProcessorType);
		LOG_INFO("PageSize: " << sysInfo.dwPageSize);
#endif

#ifndef _RELEASE
#ifndef OS_ANDROID
		fileManager.addArchive(new engine::file::DirectoryArchive("../enginedata/"));
		fileManager.addArchive(new engine::file::DirectoryArchive("../data/"));
		fileManager.addArchive(new engine::file::DirectoryArchive("."));
#endif
#endif

#ifdef OS_WEB
		// Web has the virtual filesystem, it has already the packaging and stuff, we can use the DirectoryArchive
		fileManager.addArchive(new engine::file::DirectoryArchive("./data/"));
#endif

#ifndef _EDITOR
		// Add all .pp files.

#ifndef OS_ANDROID // Android doesn't like that its filesystem is directly used.
		std::vector<String> files;

		sys::listFilesInDirectory(files, ".");

		for (unsigned i = 0; i < files.size(); ++i)
		{
			String fileName = files[i];


			if (fileName.find(".pp") != String::npos)
			{
				// its .pp file
				fileManager.addArchive(new file::PackageArchive(fileName));
			}
		}

		fileManager.addArchive(new engine::file::DirectoryArchive("./data/"));
#endif

#endif

#ifdef OS_ANDROID
		fileManager.addArchive(new engine::file::AndroidAssetManagerArchive(androidApp->activity->assetManager));
#endif

		entityTypeManager = engine::scene::EntityTypeManager(&fileManager, &context);
		running = true;

		// ##############################
		// Init systems

#if defined (OS_WINDOWS)
		rawInputSystem = new engine::input::RawInputSystem(&inputSystem, hwnd);
		systemManager.addSystem(rawInputSystem, 0);
#endif

		physicSystem = new physics::PhysicSystem(NULL);
		box2dPhysicSystem = new physics::Box2DPhysicSystem();

#if defined (RENDERING_ENABLED)
		ingameConsoleSystem = new console::IngameConsoleSystem(NULL, &inputSystem, &resourceManager, this);

		resourceManager.addResourceLoader(new engine::renderer::ShaderLoader(&fileManager, rendererSystem));
		resourceManager.addResourceLoader(new engine::renderer::PropellerModelLoader(&fileManager, rendererSystem));
#endif
		// Each configuration has its own texture loader, even nullrenderer
		resourceManager.addResourceLoader(new engine::renderer::TextureLoader(&fileManager, rendererSystem));

#if defined (OS_WINDOWS)
		xInputSystem = new engine::input::XInputSystem(&inputSystem);
		systemManager.addSystem(xInputSystem, 0);
#endif
#if defined (OS_ANDROID)
		androidInputSystem = new engine::input::AndroidInputSystem(&inputSystem);
		systemManager.addSystem(androidInputSystem, 0);
#endif

		systemManager.addSystem(&inputSystem, 3);
		systemManager.addSystem(box2dPhysicSystem, 10);

		systemManager.addSystem(physicSystem, 10);

#if defined (RENDERING_ENABLED)
		systemManager.addSystem(cameraSystem, 30);
		systemManager.addSystem(rendererSystem, 40);
		systemManager.addSystem(ingameConsoleSystem, 65);
#endif

		sceneManager = new scene::SceneManager(this);

#ifdef DEDICATED_SERVER
		serverSystem = new network::ServerSystem(scene);
		systemManager.addSystem(serverSystem, 100);
#else
		clientSystem = new network::ClientSystem(scene, &handleManager);
		systemManager.addSystem(clientSystem, 100);
#endif

		// BUILD THE CONTEXT
		context.physicSystem = physicSystem;
		context.box2dPhysicSystem = box2dPhysicSystem;
		context.rendererSystem = rendererSystem;
		context.inputSystem = &inputSystem;
		context.resourceManager = &resourceManager;
		context.cameraSystem = cameraSystem;
		// ----

		sceneManager->populateScenesFromArchives();
		// ##############################

		frames = 0;

		if (*cvar::developer && *cvar::editor == false)
			inputSystem.bindKey("KEY_ESC", "quit");

		inputSystem.bindKeyEvent("quit", this, &GameInstance::stopApplication);

		if (!gameInit())
			LOG_ERROR("Game initialization failed! Game may or may not work...");

#ifndef _EDITOR
		console->execute("exec autoexec.cfg");
#endif

		// HACK TURN THIS ON OF IF DOING NETWORKING !
		// ndef -> normal
#ifndef DEDICATED_SERVER
		sceneManager->loadScene(*cvar::defaultScene);
#endif

		sceneRefresh();

		LOG_INFO("Total of " << sceneManager->getSceneCount() << " scenes available.");
		LOG_INFO("Game initialization done!");

		currentTime = sys::Timer::getCurrentTimeInSeconds();

#ifndef DEDICATED_SERVER


// Only run rendering, networking, etc  
//HACK: Switch systems on/off depending on the client/server/standalone status!!
// 0 -> normal
#if 0
		clientSystem->connect();
		systemManager.setPaused(true);

		rendererSystem->setAmbientLight(math::Vec4(0.3f, 0.3f, 0.3f, 0.3f));

		//cameraSystem->setCameraMode(renderer::CameraSystem::CAMERAMODE_DEBUG_FREEFLY);
#endif

#endif
	}

	void GameInstance::uninit()
	{
		PROFILE;

		// reset scene first, this removes all components from systems
		scene->resetScene();

		gameUninit();

		if (*cvar::dump_profiler_on_shutdown == 1)
			engine::profiler::g_profilerManager->dumpProfilerAsJSON();

		systemManager.shutdown();

		console->saveConfig("options.cfg");

		sys::uninitNetworking();

		LOG_INFO("Shutting down the eng.getCurrentTimeInSeconds());ine!");

		LOG_WARNING("deletion of runtime systems is incomplete! (TODO)");

#if defined (RENDERING_ENABLED)
		delete rendererSystem;
#endif

		delete box2dPhysicSystem;
#if defined OS_WINDOWS
		delete rawInputSystem;
		delete xInputSystem;
#endif

		delete scene;

		sys::uninitNetworking();
	}

	void GameInstance::update()
	{
		PROFILE;

		// No updating when the engine is hibernating
		if (hibernating)
			return;

		double newTime = sys::Timer::getCurrentTimeInSeconds();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		accumulator += frameTime;

//		LOG_INFO("frametime: " << frameTime);

		while (accumulator >= dt)
		{
			scene->cleanRemovedEntities();
			gameMode->onGameRunning();
			systemManager.updateSystems(float(dt)); 
			accumulator -= dt;
			t += dt;
		}

		systemManager.renderFrame();
	}

	void GameInstance::stopApplication(bool isKeyDown)
	{
		if (isKeyDown)
			stopApplication();
	}

	//Set bit to notify that the application is closed. Underlying system should read it and get it
	//System handling GameApplication is responsible for calling the cleanups.
	void GameInstance::stopApplication()
	{
		running = false;
	}

	void GameInstance::sceneRefresh()
	{
		PROFILE;

		const engine::scene::Scene::EntityList *entities = scene->getEntityList();

		for (unsigned i = 0; i < entities->size(); ++i)
		{
			refreshEntity(entities->at(i));
		}

#ifdef _EDITOR
		scene->markEntityListDirty();
#endif
	}

	void GameInstance::refreshEntityId(unsigned id)
	{
		refreshEntity(engine::rtti::dynamicCast<engine::scene::Entity>(handleManager.getHandle(id)));
	}

	void GameInstance::refreshEntity(engine::scene::Entity *ent)
	{
		PROFILE;

		//Late bind every component that has the bind!
		engine::component::ComponentHolder::ComponentList components = ent->getComponents();

		for (unsigned x = 0; x < components.size(); ++x)
		{
			//Refresh handles if there is any!

			engine::properties::PropertyVector props = components[x]->getProperties();

			for (unsigned y = 0; y < props.size(); ++y)
			{
				if (props[y].getType() == engine::properties::PropertyTypeHandle)
				{
					props[y].refreshHandle(components[x]);
				}
			}
		}

	}

	void GameInstance::saveSceneToDisk(String fileName)
	{
		PROFILE;

		LOG_INFO("Saving scene to disk");
		engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> sceneStream;
		scene->save(sceneStream);

		std::ofstream output;

		output.open(fileName.c_str(), std::ios::binary);
		output.write((char*)sceneStream.getData(), sceneStream.getIndex());
		output.close();
	}

	void GameInstance::loadSceneFromDisk(String fileName)
	{
		PROFILE;

		LOG_INFO("Loading scene from disk");

		FILE *f = NULL;

		sys::fileOpen(&f, fileName, "rb");

		if (f == NULL)
		{
			LOG_ERROR("Cannot open scene!");
			return;
		}

		fseek(f, 0L, SEEK_END);
		size_t size = ftell(f);
		fseek(f, 0L, SEEK_SET);

		char *buffer = (char*)malloc(size);

		fread(buffer, size, 1, f);

		sys::fileClose(f);

		engine::stream::InputStream<engine::stream::SerializationEndian> stream(buffer);

		resetScene();
		scene->load(stream);

		const engine::scene::Scene::EntityList *entityList = scene->getEntityList();

		for (unsigned i = 0; i < entityList->size(); ++i)
		{
			reloadTypeDataForEntity(entityList->at(i));
		}

		sceneRefresh();

		gameMode->onSceneLoad();
	}

	void GameInstance::loadSceneFromArchive(String fileName)
	{
		PROFILE;

		resetScene();
		file::File file = fileManager.openFile(fileName);

		if (!file.isValid())
		{
			LOG_WARNING("Could not open file!");
			return;
		}

#ifndef HTML5
		loadFromStream(file->getInputStream());
#else
		LOG_ERROR("HTML5 disables stream loading!");
#endif
	}

	void GameInstance::resetScene()
	{
		PROFILE;

		gameMode->onSceneUnload();
		scene->resetScene();

		handleManager.releaseAllHandles();
	}

	void GameInstance::saveToStream(engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> &sceneStream)
	{
		PROFILE;

		scene->save(sceneStream);
	}

	void GameInstance::loadFromStream(engine::stream::InputStream<engine::stream::SerializationEndian> strm)
	{
		PROFILE;

		LOG_INFO("LoadFromStream: resetScene");
		resetScene();
		LOG_INFO("LoadFromStream: scene.load");
		scene->load(strm);
		LOG_INFO("LoadFromStream: sceneRefresh");
		sceneRefresh();

		LOG_INFO("LoadFromStream: gameMode->onSceneLoad");
		gameMode->onSceneLoad();

		LOG_INFO("Final refresh of scene!");
		sceneRefresh();
	}

	unsigned GameInstance::addEntityByType(const String &type)
	{
		return addEntityByType(type, 0, 0);
	}

	unsigned GameInstance::addEmptyEntity()
	{
		PROFILE;

		scene::Entity *ent = rtti::dynamicCast<scene::Entity>(rtti::RTTI::generateSerializable("Entity", &context));

		ent->setName("Entity");

		scene->addEntity(ent);

		return ent->getHandleId();
	}

	unsigned GameInstance::addEntityByType(const String &type, int x, int y)
	{
		PROFILE;

		scene::Entity *ent = rtti::dynamicCast<scene::Entity>(rtti::RTTI::generateSerializable("Entity", &context));

		ent->setEntityType(type);

		entityTypeManager.applyTypeOnEntity(ent);

		engine::scene::TransformComponent *transform = ent->findComponent<engine::scene::TransformComponent>();
		if (transform == NULL)
		{
			//If not transform, add it to the entity.
			transform = rtti::dynamicCast<scene::TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", &context));
			ent->addComponent(transform);
		}

		transform->setPosition(math::Vec3((float)x, (float)y, 1.0f));

		scene->addEntity(ent);

		//Refresh possible data that has not been binded
		refreshEntity(ent);

		return ent->getHandleId();
	}

	void GameInstance::reloadTypeDataForEntity(engine::scene::Entity *entity)
	{
		PROFILE;
		// Recreate entity based on the type data from the disk.
		entityTypeManager.applyTypeOnEntity(entity);
	}

	void GameInstance::reloadTypeData()
	{
		PROFILE;
		// Loop trough entities and apply type

		engine::scene::Scene::EntityList *entities = scene->getEntities();

		engine::scene::Scene::EntityList::iterator it = entities->begin();

		while (it != entities->end())
		{
			entityTypeManager.applyTypeOnEntity(*it);
			++it;
		}

		// refresh the scene, because some data changes may have reseted the state.
		sceneRefresh();
	}

	void GameInstance::createNewEntityType(String name)
	{
		entityTypeManager.createNewEntityType(name);
	}

	void GameInstance::setGameMode(GameMode *mode)
	{
		gameMode = mode;
		gameMode->setInstance(this);
	}

	// Hibernate the engine, remove all GPU-assets, drop GPU context and stop updating
	void GameInstance::hibernate()
	{
#ifndef NULLRENDERER
		LOG_INFO("[GameInstance] Hibernating...");
		hibernating = true;

		// Remove stuff from the resourceManager, no cached false files when reloading
		resourceManager.prepareHibernation();

		// Destroy context
		rendererSystem->uninit();

		LOG_INFO("[GameInstance] Hibernated!");

		//TODO: go trough components and invalidate ptr's (optional)
#endif
	}

	// Resume from hibernation, recreate GPU context, force reload on all assets (sprite, shaders) and continue updating
	void GameInstance::wakeup(intptr_t hwnd)
	{
#ifndef NULLRENDERER
		LOG_INFO("[GameInstance] Waking up...");
		hibernating = false;

		// Recreate context
		rendererSystem->setHWND(hwnd); // give the rendere system the new hwnd
		rendererSystem->init();

		// Reload GPU resources on components
		rendererSystem->reloadAssets();

		LOG_INFO("[GameInstance] Wakeup from hibernation done!");
#endif
	}

}

//Runtimecompiler interface

#ifdef _EDITOR

namespace runtimecompiled {

	extern "C" void __declspec(dllexport) *getRuntimeCompiledData()
	{
		return engine::rtti::g_classSet;
	}

	extern "C" void __declspec(dllexport) setRuntimeHandleManager(void *handleManager)
	{
		DEBUG_PRINT("Updating g_runtimeHandleManager ptr.");
		//TODO: possibly leaking the old manager here...
		LOG_ERROR("Setting runtime handle manager is not implemented!");
		//engine::lang::g_runtimeHandleManager = (engine::lang::HandleManager*)handleManager;
	}
}

#endif
