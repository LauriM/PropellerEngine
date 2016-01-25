// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITORBACKEND_GAMEVIEW_H
#define EDITORBACKEND_GAMEVIEW_H

#include "game/Propeller.h"

#include "editorbackend/CSharp/CSharpInstance.h"
#include "engine/sys/GameWindow.h"

PROPELLER_FORWARD_DECLARE_1(editor, EditorVisualizationSystem);

namespace editor {

	// separated window to run the game in
	class GameView : public CSharpInstance
	{
	private: 
		PrimaryGameInstance gameInstance;
		engine::sys::GameWindow *window;

	public:
		bool init();
		void uninit();

		void startup(intptr_t ptr);

		void update();
	};

}

#endif