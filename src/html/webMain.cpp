// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "precompiled.h"

#include "game/DummyGameInstance.h"

#include "game/sys/ConsoleLogger.h"

#include <stdio.h>
#include <emscripten.h>
#include <html5.h>

#include "keycodes.h"

game::DummyGameInstance gameInstance;

void loop()
{
	gameInstance.update();
}

EM_BOOL keyDown (int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
{
	gameInstance.getInputSystem()->keyDown(webkeyToPropellerKey[keyEvent->keyCode]);

	if (webkeyToPropellerKey[keyEvent->keyCode] == engine::input::KEY_VOID)
		return false;
	else
		return true;
}

EM_BOOL keyUp(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData)
{
	gameInstance.getInputSystem()->keyUp(webkeyToPropellerKey[keyEvent->keyCode]);

	if (webkeyToPropellerKey[keyEvent->keyCode] == engine::input::KEY_VOID)
		return false;
	else
		return true;
}

int main()
{
	setupKeys();// setup the HTML key mappings

	emscripten_set_canvas_size(800, 600);

	printf("hello world!\n");

	std::ifstream f;
	f.open( "./data/pyramid.PropellerModel", std::ifstream::binary );

	if(f.is_open())
		printf("file open ok!\n");
	else
		printf("file open not ok :< \n");

	engine::sys::addLogger(new game::sys::ConsoleLogger());


	printf("initting rendering\n");

	gameInstance.initializeRenderer(NULL);

	printf("starting init()\n");

	{
		engine::file::FileList files;
		gameInstance.getFileManager()->listFiles(files);

		engine::file::FileList::FileArray arr = files.getFiles();

		LOG_INFO("listing files, count: " << arr.size());
		for (unsigned i = 0; i < arr.size(); ++i)
			LOG_INFO(" * " << arr[i]);
	}

	gameInstance.getConsole()->execute("set defaultScene phys");

	gameInstance.init();

	{
		engine::file::FileList files;
		gameInstance.getFileManager()->listFiles(files);

		engine::file::FileList::FileArray arr = files.getFiles();

		LOG_INFO("listing files, count: " << arr.size());
		for (unsigned i = 0; i < arr.size(); ++i)
			LOG_INFO(" * " << arr[i]);
	}

	gameInstance.getConsole()->execute("echo OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
	gameInstance.getConsole()->execute("ls");
	gameInstance.getConsole()->execute("filemanagerlist");

	gameInstance.getConsole()->execute("listcommands");
	gameInstance.getConsole()->execute("listcvars");
	gameInstance.getConsole()->execute("systemlist");
	gameInstance.getConsole()->execute("ls");
	gameInstance.getConsole()->execute("setpos -2.8281 -1.2858 1.918");

	gameInstance.getConsole()->execute("bind KEY_W playerup");
	gameInstance.getConsole()->execute("bind KEY_S playerdown");
	gameInstance.getConsole()->execute("bind KEY_A playerleft");
	gameInstance.getConsole()->execute("bind KEY_D playerright");

	printf("init done\n");

	printf("total of %i systems registered.\n", gameInstance.getSystemManager()->getSystemList().size());

	gameInstance.update();

	emscripten_set_keydown_callback(NULL, NULL, true, &keyDown);
	emscripten_set_keyup_callback(NULL, NULL, true, &keyUp);

	emscripten_set_main_loop(loop, 60, 1);

	return 0;
}
