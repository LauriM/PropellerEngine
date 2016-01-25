// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "engine/stream/OutputStream.h"
#include "engine/stream/CallWithStream.h"

#include "engine/scene/Entity.h"
#include "engine/sys/Logger.h"

#include <stdio.h>

bool logInitOk = false;

extern "C" __declspec(dllexport) int testCall(int value)
{
	return value * 2;
}

extern "C" __declspec(dllexport) editor::CSharpInstance* __stdcall createInstance(const char *name)
{
	if (logInitOk == false)
	{
		//TODO: fix this damn preinit stuff that needs to be updated everywhere
		engine::sys::initLogging();
		engine::sys::initTimer();

		logInitOk = true;
	}

	return editor::CSharpInstanceManager::create(name);
}

extern "C" __declspec(dllexport) void __stdcall releaseInstance(editor::CSharpInstance *instance)
{
	editor::CSharpInstanceManager::release(instance);
}

extern "C" __declspec(dllexport) void __stdcall syncInstance(editor::CSharpInstance *inst, const char *in, char **out)
{
	editor::CSharpInstanceManager::syncCSharpInstance(inst, in, out);
}

extern "C" __declspec(dllexport) void __stdcall finalizeSync(editor::CSharpInstance *instance)
{
	editor::CSharpInstanceManager::finalizeSync(instance);
}
