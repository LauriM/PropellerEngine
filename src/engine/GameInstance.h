// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_GAMEAPPLICATION_H
#define ENGINE_GAMEAPPLICATION_H

#ifdef OS_ANDROID
#include <android_native_app_glue.h>
#endif

#include "engine/console/Console.h"
#include "engine/resource/ResourceManager.h"
#include "engine/file/FileManager.h"
#include "engine/stream/BufferedOutputStream.h"
#include "engine/scene/EntityTypeManager.h"
#include "engine/physics/PhysicSystem.h"
#include "engine/SystemManager.h"
#include "engine/scene/Scene.h"
#include "engine/input/RawInputSystem.h"
#include "engine/input/InputSystem.h"
#include "engine/input/XInputSystem.h"
#include "engine/scene/Scene.h"
#include "engine/Context.h"
#include "engine/lang/ScopedPtr.h"
#include "engine/lang/HandleManager.h"
#include "engine/sys/Scheduler.h"

PROPELLER_FORWARD_DECLARE_2(engine, renderer, RendererSystem);
PROPELLER_FORWARD_DECLARE_2(engine, input, AndroidInputSystem);
PROPELLER_FORWARD_DECLARE_1(engine, GameMode);
PROPELLER_FORWARD_DECLARE_2(engine, scene, SceneManager);
PROPELLER_FORWARD_DECLARE_2(engine, console, IngameConsoleSystem);
PROPELLER_FORWARD_DECLARE_2(engine, physics, Box2DPhysicSystem);
PROPELLER_FORWARD_DECLARE_2(engine, network, ServerSystem);
PROPELLER_FORWARD_DECLARE_2(engine, network, ClientSystem);

#define PROPELLER_REGISTER_PRIMARY_INSTANCE(p_name) typedef p_name PrimaryGameInstance;

namespace engine {

	class GameInstance
	{
	private:
#if defined OS_WINDOWS
		HWND hwnd;
#endif
		GameMode *gameMode;
		int frames;
		bool running;
		long lastFrameTimeInMs;

		sys::Scheduler scheduler;
		lang::HandleManager handleManager;
		lang::ScopedPtr<engine::console::Console> console;
		engine::resource::ResourceManager resourceManager;
		engine::file::FileManager fileManager;
		engine::scene::Scene *scene;
		engine::scene::EntityTypeManager entityTypeManager;
		engine::network::ServerSystem *serverSystem;
		engine::network::ClientSystem *clientSystem;

		// Default Systems
		engine::physics::PhysicSystem *physicSystem;
		engine::physics::Box2DPhysicSystem *box2dPhysicSystem;
		engine::input::InputSystem inputSystem;
		engine::input::RawInputSystem *rawInputSystem;
		engine::renderer::CameraSystem *cameraSystem;
		engine::renderer::RendererSystem *rendererSystem;
		engine::console::IngameConsoleSystem *ingameConsoleSystem;

#if defined OS_WINDOWS
		engine::input::XInputSystem *xInputSystem;
#endif

#if defined OS_ANDROID
		engine::input::AndroidInputSystem *androidInputSystem;
#endif

		void stopApplication();
		void stopApplication(bool isKeyDown);

		void reloadTypeDataForEntity(engine::scene::Entity *entityId);

#if defined OS_ANDROID
	struct android_app *androidApp;
#endif
	protected:
		ContextData context;

		engine::SystemManager systemManager;
		engine::scene::SceneManager *sceneManager;

	private:
		const double dt = 0.01;
		double accumulator;
		double currentTime;
		double t;

		bool hibernating;

	public:
#if defined OS_ANDROID
		void setAndroidApp(android_app *app) { androidApp = app; }
		struct android_app *getAndroidApp() const { return androidApp; }
#endif
		unsigned addEmptyEntity();
		unsigned addEntityByType(const String &type);
		unsigned addEntityByType(const String &type, int x, int y);

		GameInstance();

		void initializeRenderer(intptr_t hwnd);
		void init();
		void uninit();

		void update();

		// Hibernate the engine, remove all GPU-assets, drop GPU context and stop updating
		void hibernate();

		// Resume from hibernation, recreate GPU context, force reload on all assets (sprite, shaders) and continue updating
		void wakeup(intptr_t hwnd);


		virtual bool gameInit() = 0;
		virtual void gameUninit() = 0;

		void setGameMode(GameMode *mode);

		void saveToStream(engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> &sceneStream);
		void loadFromStream(engine::stream::InputStream<engine::stream::SerializationEndian> strm);

		void saveSceneToDisk(String fileName);
		void loadSceneFromDisk(String fileName);
		void loadSceneFromArchive(String fileName);

		void resetScene();

		// Refresh all handles and resources, used after loading the scene.
		void sceneRefresh();
		void refreshEntityId(unsigned id);
		void refreshEntity(engine::scene::Entity *ent);

		// Entity Type Manager stuff
		void reloadTypeData();
		void createNewEntityType(String name);

		SHAREDENGINE engine::scene::Scene *getScene() { return scene; }
		SHAREDENGINE engine::scene::EntityTypeManager *getEntityTypeManager() { return &entityTypeManager; }
		engine::file::FileManager *getFileManager() { return &fileManager; }
		engine::console::Console *getConsole() { return console.getPtr(); }
		engine::SystemManager *getSystemManager() { return &systemManager; }
		engine::resource::ResourceManager *getResourceManager() { return &resourceManager; }
		engine::input::InputSystem *getInputSystem() { return &inputSystem; }
		engine::scene::SceneManager *getSceneManager() const { return sceneManager; }
		SHAREDENGINE engine::renderer::CameraSystem *getCameraSystem() const { return cameraSystem; }
		SHAREDENGINE engine::lang::HandleManager *getHandleManager() { return &handleManager; }
		engine::network::ServerSystem *getServerSystem() { return serverSystem; }
		engine::physics::Box2DPhysicSystem *getBox2DPhysicSystem() const { return box2dPhysicSystem; }

		// Provide the context that has ptrs to all of the relevant systems
		engine::ContextData *getContextData() { return &context; }

		const bool isRunning() const { return running; }
		SHAREDENGINE const long getLastFrameTimeInMs() const { return lastFrameTimeInMs; }

#if defined (OS_ANDROID)
		engine::input::AndroidInputSystem *getAndroidInputSystem() { return androidInputSystem; }
#endif
	};

}

#ifdef _EDITOR

namespace runtimecompiled {

	extern "C" void __declspec(dllexport) *getRuntimeCompiledData();
	extern "C" void __declspec(dllexport) setRuntimeHandleManager(void *handleManager);

}

#endif //_EDITOR

#endif // header guard
