// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.

#include "standalone/precompiled.h"

#include "game/Propeller.h"

#include "engine/console/Console.h"
#include "engine/console/Command.h"
#include "engine/preprocessor/version.h"
#include "engine/sys/GameWindow.h"
#include "standalone/sys/FileLogger.h"
#include "engine/sys/Sleep.h"
#include "standalone/sys/DebugLogger.h"
#include "engine/console/IngameLogger.h"
#include "engine/console/Cvar.h"

using namespace engine::sys;
using namespace game;

namespace cvar {
	EXTERN_CVAR(int, r_width);
	EXTERN_CVAR(int, r_height);
}

// Run the game
void runGame()
{
	PrimaryGameInstance game;

#if defined (OS_LINUX) || defined (OS_MAC)
	// Linux is only used as a testing platform right now
	engine::sys::addLogger(new standalone::FileLogger("engine.log"));

	game.initializeRenderer(NULL); // only windows platform currently has supported rendering stuff
	game.init();

	for (unsigned i = 0; i < 50; ++i)
	{
		game.update();
	}

	game.uninit();

#else
	GameWindow *window = new GameWindow("PropellerEngine", *cvar::r_width, *cvar::r_height);

	if (window->isClosed())
	{
		LOG_ERROR("Could not init window!");
		return;
	}

	game.initializeRenderer((intptr_t)window->getWindowHandle());

	game.init();

	//	game.loadSceneFromArchive("lol.PropellerScene");

	bool tick = true;
	int t = 500;

	while (game.isRunning())
	{
		PROFILE;

		game.update();

		if (window->isClosed())
			break;

		/*
		--t;
		if (t < 0)
		{

			if (tick == true)
			{
				game.hibernate();

				window->close();
				delete window;

				tick = false;
				t = 500;

				LOG_INFO("sleep..");

				engine::sys::propellerSleep(3000);

				window = new GameWindow("NEW CONTEXT PROPELL", *cvar::r_width, *cvar::r_height);

				game.wakeup((intptr_t)window->getWindowHandle ());
			}

		}
		*/
	}

	engine::sys::propellerSleep(500);

	game.getConsole()->execute("getpos");

	game.uninit();

#endif
}


// Run the game
void runServer()
{
	PrimaryGameInstance game;

	game.initializeRenderer(NULL);
	game.init();

	while (game.isRunning())
	{
		PROFILE;

		game.update();
	}

	game.uninit();
}

#ifdef OS_WINDOWS
#ifndef DEDICATED_SERVER
	int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
#else
	int main()
#endif
#else
	int main()
#endif
{
	PROFILE;

	engine::sys::initLogging();
	engine::sys::initTimer();

#ifdef _RELEASE
	engine::sys::addLogger(new standalone::FileLogger("engine.log"));
#else
	engine::sys::addLogger(new game::sys::DebugLogger());
	engine::sys::addLogger(new console::IngameLogger());
#endif

	LOG_INFO("# " << GAME_NAME " #");
	LOG_INFO("Engine version : " << ENGINE_VERSION_MAJOR << "." << ENGINE_VERSION_MINOR);
	LOG_INFO("Game version   : " << GAME_VERSION_MAJOR << "." << GAME_VERSION_MINOR);

#ifdef DEDICATED_SERVER
		LOG_INFO("## Dedicated server mode ##");
		runServer();
#else
		runGame();
#endif

    return 0;
}
