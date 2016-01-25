// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/GameEditor.h"

#include "game/Propeller.h"
#include "editorbackend/CSharp/CSharpInstance.h"
#include "editorbackend/CSharp/CSharpInstanceType.h"
#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "editorbackend/sys/EditorLogger.h"
#include "editorbackend/EntityEditView.h"
#include "engine/scene/Entity.h"
#include "engine/sys/Logger.h"
#include "editorbackend/entityeditor/EntityEditTargetType.h"
#include "engine/scene/EntityTypeManager.h"
#include "engine/scene/Scene.h"
#include "engine/console/IngameLogger.h"
#include "editorbackend/tiledimport/TiledImporter.h"
#include "editorbackend/EditorVisualizationSystem.h"

//TODO: Runtimecompiled, check if this is needed
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' "\
	"version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

engine::sys::Logger *g_logger;

namespace editor {

	REGISTER_CSHARPINSTANCE(GameEditor);

	bool GameEditor::init()
	{
		engine::sys::addLogger(new editor::sys::EditorLogger(this));
		engine::sys::addLogger(new engine::console::IngameLogger());

#ifdef RCCPP
		getRuntimeCompiledData = &runtimecompiled::getRuntimeCompiledData;

		reloadRuntimeModule();
#endif

		//loadRuntimeModule(); //Runtime module is not yet loaded! The rendering should use the Game.dll
		registerEvent("update", this, &GameEditor::instanceUpdateProxy);
		registerEvent("initializeRenderer", dynamic_cast<engine::GameInstance*>(&gameInstance), &PrimaryGameInstance::initializeRenderer);
		registerEvent("initialize", this , &GameEditor::instanceInitProxy);
		registerEvent("saveScene", dynamic_cast<engine::GameInstance*>(&gameInstance), &engine::GameInstance::saveSceneToDisk);
		registerEvent("loadScene", this, &GameEditor::sceneLoadProxy);
		registerEvent("reloadDLL", this, &GameEditor::reloadRuntimeChanges);

		registerEvent("callCCommand", this, &GameEditor::callCCommand);

		// Editor usage
		registerEvent("removeEntity", this , &GameEditor::removeEntityByHandleId);

		// Movement input
		registerEvent("keyDown", this, &GameEditor::keyDown);
		registerEvent("keyUp", this, &GameEditor::keyUp);
		registerEvent("mouseDeltaInput", this, &GameEditor::mouseDeltaInput);

		// EntityType 
		registerEvent("syncEntityTypesToDisk", this, &GameEditor::syncEntityTypesToDisk);
		registerEvent("createNewEntityType", this, &GameEditor::createNewEntityType);

		// Assetbrowser
		registerEvent("reloadArchiveBrowserList", this, &GameEditor::reloadArchiveBrowserList);

		// Misc
		registerEvent("importTiledMap", this, &GameEditor::importTiledMap);
		registerEvent("toggle2D3D", this, &GameEditor::toggle2D3D);

		// test commands 
		registerEvent("test", this, &GameEditor::testPrint);

		// pausing & running the engine
		registerEvent("stopEngine", this, &GameEditor::stopEngine);
		registerEvent("pauseEngine", this, &GameEditor::pauseEngine);
		registerEvent("runEngine", this, &GameEditor::runEngine);

		registerEvent("requestGameViewLaunch", this, &GameEditor::requestGameViewLaunch);

		gameInstance.getConsole()->execute("exec editor.cfg");
		gameInstance.getSystemManager()->setPaused(true);

		LOG_INFO("GameEditor pre-init done!");

		stopped = true;

		return true;
	}

	void GameEditor::syncEntityTypesToDisk()
	{
		gameInstance.getEntityTypeManager()->saveTypesToDisk();
	}


	void GameEditor::createNewEntityType(String name)
	{
		gameInstance.createNewEntityType(name);

		// After creation, reload archive browser.
		syncEntityTypesToDisk();
	}

	void GameEditor::reloadArchiveBrowserList()
	{
		clearArchiveBrowserNodes();
		refreshArchiveBrowser();
	}

	void GameEditor::sceneLoadProxy(String fileName)
	{
		entityListClear(); // clear the entity list in the GUI

		//Load the level, should trigger addEntities, which should trigger the ui updates.
		gameInstance.loadSceneFromDisk(fileName);
	}

	void GameEditor::instanceUpdateProxy()
	{
		//First, update the instance
		gameInstance.update();

		//Lets check if there are new entities to update to the GUI

		if (gameInstance.getScene()->isEntityListDirty())
		{
			//Find added objects
			const engine::scene::Scene::EntityList *entList = gameInstance.getScene()->getEntityList();

			for (unsigned i = 0; i < entList->size(); ++i)
			{
				engine::scene::Entity *ptr = entList->at(i);

				if (ptr->isEntityDirty())
				{ 
					entityListAddNode(ptr->getHandleId(), ptr->getName());
					ptr->setDirty(false);
				}
			}

			//Check for removed objects!
			const engine::scene::Scene::RemovedHandleList removedList = gameInstance.getScene()->getRemovedHandleList();

			for(unsigned i = 0; i < removedList.size(); ++i)
			{
				entityListRemoveNode(removedList[i]);
			}

			//Clear the list as we have checked themmesh.type
			gameInstance.getScene()->clearRemovedHandles();

			// Check for updated objects
			const engine::scene::Scene::RenamedHandleList renamedList = gameInstance.getScene()->getRenamedHandleList();

			for (unsigned i = 0; i < renamedList.size(); ++i)
			{
				engine::scene::Entity *ent = engine::rtti::dynamicCast<engine::scene::Entity>(gameInstance.getHandleManager()->getHandle(renamedList[i]));
				entityListRenameEntity(renamedList[i], ent->getName());
			}

			gameInstance.getScene()->clearRenamedHandles();
		}
	}

	//This proxies the game init. This allows for "post init" stuff from the "GameEditor" to be executed after the engine is ready.
	void GameEditor::instanceInitProxy()
	{
		gameInstance.init();
		refreshArchiveBrowser();

		//Add component class names!

		std::vector<engine::rtti::Class*> types;

		engine::rtti::RTTI::getDerivedForTypeName("Component", &types);

		for (unsigned i = 0; i < types.size(); ++i)
			call("addComponentClassName", types[i]->getTypeName(), types[i]->getSourcePath() );


		editorVisualizationSystem = new EditorVisualizationSystem(NULL); //Note: debugdrawsystem has been deprecrated, this is why the input is NULL

		gameInstance.getSystemManager()->addSystem(editorVisualizationSystem, 62);
	}

	void GameEditor::uninit()
	{
		gameInstance.uninit();
	}

	void GameEditor::entityListAddNode(int id, String name)
	{
		call("entityListAddNode", id, name);
	}

	void GameEditor::entityListRemoveNode(int id)
	{
		call("entityListRemoveNode", id);
	}

	void GameEditor::entityListRenameEntity(unsigned entityId, const String name)
	{
		call("entityListRenameEntity", entityId, name);
	}

	void GameEditor::testPrint(int val)
	{
		sendMessage("Hello From c++!");
		entityListAddNode(0,"Test node hehe");
		entityListAddNode(0,"moi");
	}

	//C# stuff (These calls forward into the c#)

	void GameEditor::sendMessage(String msg)
	{
		call("addMessage", msg);
	}

	void GameEditor::logInfo(String msg)
	{
		call("logInfo", msg);
	}

	void GameEditor::logWarning(String msg)
	{
		call("logWarning", msg);
	}

	void GameEditor::logError(String msg)
	{
		call("logError", msg);
	}

	void GameEditor::addEntity(String entName)
	{
		call("addEntity", entName);
	}

	void GameEditor::removeEntity(String entName)
	{
		call("removeEntity", entName);
	}

	void GameEditor::entityListClear()
	{
		call("entityListClear");
	}

	void GameEditor::addArchiveBrowserNode(String type)
	{
		call("addNode", type);
	}

	void GameEditor::clearArchiveBrowserNodes()
	{
		call("clearNodes");
	}

	//Adds RTTI named component to the list on the C# side, used for GUI listings.
	void GameEditor::addComponentClassName(String name)
	{
		call("addComponentClassName", name);
	}

	void GameEditor::reloadRuntimeChanges()
	{
		//Save and load from stream here / smart serialization trick
		engine::stream::BufferedOutputStream<engine::stream::NativeEndian> outputStream;

		gameInstance.saveToStream(outputStream);
		gameInstance.resetScene();

		reloadRuntimeModule();

		//engine::lang::getHandleManager()->releaseAllHandles();
		LOG_ERROR("Hacked handlemanager to reset!");
		//engine::lang::setHandleManager((engine::lang::HandleManager*)NULL);//TODO: FIX THIS DAMNIT

		engine::stream::InputStream<engine::stream::NativeEndian> inputStream((void*)outputStream.getData());

		gameInstance.loadFromStream(inputStream);
	}

	void GameEditor::reloadRuntimeModule()
	{
		loadRuntimeModule();

		//TODO: heavy optimization here!

		// Set the farproc to use the main handlemanager in the main .dll
		//setRuntimeHandleManagerOnFarProc(engine::lang::g_runtimeHandleManager);


		//TODO: HANDLE MANAGER IS NOW LOCAL, NOT GLOBAL, NEEDS TO BE FIXED !! ! !

		// Merge information from the new .dll into the main dll
		engine::rtti::ClassSet *newSet = (engine::rtti::ClassSet*)getRuntimeCompiledData();

		engine::rtti::ClassSet::iterator it = newSet->begin();

		while (it != newSet->end())
		{
			String name = it->first;

			engine::rtti::ClassSet::iterator originalIt = engine::rtti::g_classSet->find(name);

			if (originalIt == engine::rtti::g_classSet->end())
			{
				DEBUG_PRINT("STUFF IN NEW SET THATS NOT IN OLD!");

				// Recreating the data
				engine::rtti::Class *cls = new engine::rtti::Class(*it->second);

				engine::rtti::g_classSet->insert(engine::rtti::ClassSet::value_type(name, cls));
				++it;
				continue;
			}

			// OVERWRITE DATA WITH NEW DATA
			originalIt->second->setClassFactory((engine::rtti::Object *(*)(void*))it->second->getClassFactory());

			// Find a baseClass ptr on the ORIGINAL set that has the same NAME as the data in the new .dll
			const engine::rtti::Class *newBaseClass = it->second->getBaseClass();

			if (newBaseClass != NULL) // if null, no baseclass check required
			{
				String baseClassTypeName = newBaseClass->getTypeName();

				engine::rtti::ClassSet::iterator baseClassIterator = engine::rtti::g_classSet->find(baseClassTypeName);

				if (baseClassIterator == engine::rtti::g_classSet->end())
					LOG_ERROR("Could not find baseclass for: " << baseClassTypeName << " during RTTI merge!");
				
				originalIt->second->setBaseClass(baseClassIterator->second);
			}

			engine::rtti::Class *cls = originalIt->second;

			++it;
		}
	}

	void GameEditor::loadRuntimeModule()
	{
		static unsigned counter = 0;

		std::stringstream ss;
		ss << "Game.dll.tmp";
		ss << counter;

		String libString = ss.str();
		const char *libName = libString.c_str();

		if (counter == 0) //first dll is not runtime compiled
			libName = "Game.dll";

		g_instanceModule = LoadLibraryA(libName);

		DWORD err = GetLastError();
		LOG_INFO("loading dll: " << ss.str());

		//assert(err == 0);
		DEBUG_PRINT("DLL LOADING ERR: " << err);

		FARPROC proc = GetProcAddress(g_instanceModule, "getRuntimeCompiledData");
		err = GetLastError();
		getRuntimeCompiledData = reinterpret_cast<GetRuntimeCompiledDataType>(proc);

		proc = GetProcAddress(g_instanceModule, "setRuntimeHandleManager");
		err = GetLastError();
		setRuntimeHandleManagerOnFarProc = reinterpret_cast<SetRuntimeHandleManager>(proc);

		++counter;
	}

	void GameEditor::refreshArchiveBrowser()
	{
		engine::file::FileList fileList;

		gameInstance.getFileManager()->listFiles(fileList);

		const std::vector<String> files = fileList.getFiles();

		for (unsigned i = 0; i < files.size(); ++i)
		{
			addArchiveBrowserNode(files[i]);
		}

	}

	unsigned GameEditor::addEmptyEntity()
	{
		return gameInstance.addEmptyEntity();
	}

	unsigned GameEditor::addEntityByType(String type, int x, int y)
	{
		return gameInstance.addEntityByType(type, x, y);
	}

	void GameEditor::removeEntityByHandleId(unsigned entityId)
	{
		gameInstance.getScene()->removeEntityById(entityId);
	}

	void GameEditor::callCCommand(String command)
	{
		gameInstance.getConsole()->execute(command);
	}

	void GameEditor::keyUp(int keyCode)
	{
		gameInstance.getInputSystem()->keyUp(engine::input::KeyCode(keyCode));
	}

	void GameEditor::keyDown(int keyCode)
	{
		gameInstance.getInputSystem()->keyDown(engine::input::KeyCode(keyCode));
	}

	void GameEditor::mouseDeltaInput(float x, float y)
	{
		gameInstance.getInputSystem()->axisMove(engine::input::MOUSE, x, y);
	}

	void GameEditor::importTiledMap(String filename)
	{
		TiledImporter::importTiledFile(filename, &gameInstance);
	}

	void GameEditor::toggle2D3D()
	{
		gameInstance.getConsole()->execute("toggle dimensions 2 3");
	}

	void GameEditor::pauseEngine()
	{
		gameInstance.getSystemManager()->setPaused(true);
	}

	void GameEditor::stopEngine()
	{
		if (stopped)
			return; // engine already stopped, nothing to do

		entityListClear(); // clear the entity list in the GUI

		gameInstance.resetScene();
		gameInstance.loadFromStream(engine::stream::InputStream<engine::stream::NativeEndian>(sceneBeforePlay.getData()));
		gameInstance.getSystemManager()->setPaused(true);

		sceneBeforePlay.reset();

		stopped = true;
	}

	void GameEditor::runEngine()
	{
		if (stopped)
		{
			// Engine is currently stopped, run new play session!
			gameInstance.getScene()->save(sceneBeforePlay); 
			gameInstance.getSystemManager()->setPaused(false);
			stopped = false;
		}
		else
		{
			// Engine is currently running, but paused, continue running it
			gameInstance.getSystemManager()->setPaused(false);
		}
	}

	void GameEditor::requestGameViewLaunch()
	{
		// build stream, call
		sceneForGameView.reset();

		gameInstance.getScene()->save(sceneForGameView);

		call("launchGameView", (intptr_t)sceneForGameView.getData());
	}

}