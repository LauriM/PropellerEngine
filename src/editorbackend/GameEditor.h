// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITORBACKEND_GAMEEDITOR_H
#define EDITORBACKEND_GAMEEDITOR_H

#include "editorbackend/CSharp/CSharpInstance.h"
#include "game/Propeller.h"

#include "engine/stream/BufferedOutputStream.h"

PROPELLER_FORWARD_DECLARE_1(editor, EditorVisualizationSystem);

namespace editor {

	class GameEditor : public CSharpInstance
	{
	public:
		bool init();
		void uninit();

	private:
		PrimaryGameInstance gameInstance;

		//Runtimecompiled stuff
		HMODULE g_instanceModule;

		typedef void *(*GetRuntimeCompiledDataType)(void);
		GetRuntimeCompiledDataType getRuntimeCompiledData;
		//GetRuntimeCompiledDataType getRuntimeCompiledData = 0;

		typedef void *(*SetRuntimeHandleManager)(void *handleManager);
		SetRuntimeHandleManager setRuntimeHandleManagerOnFarProc;

		// Editor related systems
		EditorVisualizationSystem *editorVisualizationSystem;

		// Contains the scene before its played, its reverted back after the play is done
		engine::stream::BufferedOutputStream<engine::stream::NativeEndian> sceneBeforePlay;
		engine::stream::BufferedOutputStream<engine::stream::NativeEndian> sceneForGameView;

		bool stopped; // is the engine in stopped stage, different from engines "paused" state

	public:
		// General editor stuff
		void addComponentClassName(String name);

		// Proxies
		void instanceInitProxy();
		void instanceUpdateProxy();
		void sceneLoadProxy(String fileName);

		// RuntimeCompiled stuff
		void reloadRuntimeModule();
		void loadRuntimeModule();

		// Debug stuff
		void testPrint(int val);

		// Commands for the C#    (MODIFY THE STATE OF THE UI)
		void reloadRuntimeChanges();
		void sendMessage(String msg); //Used for logging
		void addEntity(String entName);
		void removeEntity(String entName);
		void keyUp(int keyCode);
		void keyDown(int keyCode);
		void mouseDeltaInput(float x, float y);
		void callCCommand(String command);

		// Logging
		void logInfo(String msg);
		void logWarning(String msg);
		void logError(String msg);

		// Entity List on the GUI
		void entityListAddNode(int id, String name);
		void entityListRemoveNode(int id);
		void entityListClear();
		void entityListRenameEntity(unsigned entityId, const String name);

		// EntityTypes
		void syncEntityTypesToDisk(); 
		void createNewEntityType(String name);

		// Assets / Archive Browser on the GUI
		void addArchiveBrowserNode(String type);
		void clearArchiveBrowserNodes();
		void reloadArchiveBrowserList();

		// Scene editing
		unsigned addEmptyEntity();
		unsigned addEntityByType(String type, int x, int y);
		void removeEntityByHandleId(unsigned entityId);

		// Tiled importer triggering
		void importTiledMap(String filename);

		// other stuff
		void toggle2D3D();

		// Running and pausing the game
		void pauseEngine();
		void stopEngine();
		void runEngine();

		void requestGameViewLaunch();

		// Getters & Setters
		const engine::GameInstance *getGameInstance() const { return &gameInstance; }
		engine::GameInstance *getGameInstance() { return &gameInstance; }

	private:
		void refreshArchiveBrowser();
	};

}

#endif