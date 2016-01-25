// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/GameView.h"

#include "editorbackend/CSharp/CSharpInstance.h"
#include "editorbackend/CSharp/CSharpInstanceType.h"
#include "editorbackend/CSharp/CSharpInstanceManager.h"

#include "engine/scene/SceneManager.h"

#include "engine/stream/InputStream.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(GameView);

	bool GameView::init()
	{
		registerEvent("update", this, &GameView::update);
		registerEvent("startup", this, &GameView::startup);

		window = new engine::sys::GameWindow("PropellerEditor - GameView", 800, 600);

		gameInstance.initializeRenderer((intptr_t)window->getWindowHandle());
		gameInstance.init();

		window->inputSystem = gameInstance.getInputSystem();

		gameInstance.getConsole()->execute("exec autoexec.cfg");

		return true;
	}

	void GameView::startup(intptr_t ptr)
	{
		engine::stream::InputStream<engine::stream::NativeEndian> *strm = (engine::stream::InputStream<engine::stream::NativeEndian>*)ptr;

		gameInstance.loadFromStream(strm);
	}

	void GameView::uninit()
	{
		gameInstance.uninit();

		delete window;
	}

	void GameView::update()
	{
		gameInstance.update();

		if (window->isClosed())
		{
			call("kill");
		}
	}

}