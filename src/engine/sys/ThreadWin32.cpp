// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined(OS_WINDOWS)

#include "engine/sys/Thread.h"

namespace engine {
namespace sys {

	struct Win32Thread
	{
		Thread header;

		HANDLE threadHandle;
		DWORD threadId;
	};

	DWORD WINAPI win32ThreadEntryPoint(LPVOID lpParam)
	{
		Win32Thread *t = (Win32Thread*)lpParam;
		LOG_INFO(">> [Thread] Starting: " << t->header.name);

		t->header.entryPoint(t->header.userData);

		LOG_INFO(">> [Thread] Finished: " << t->header.name);

		t->header.running = false; // Do not delete the thread, there needs to be away to control the thread state
		return 0;
	}

	Thread *propellerCreateThread(String name, void(*entryPoint)(void *), void *userData)
	{
		Win32Thread *thread = new Win32Thread();
		thread->header.name = name;
		thread->header.running = true;
		thread->header.entryPoint = entryPoint;
		thread->header.userData = userData;

		thread->threadHandle = CreateThread(
			NULL,                   // default security attributes
			0,                      // use default stack size
			win32ThreadEntryPoint,  // thread function name
			thread,          // argument to thread function
			0,                      // use default creation flags
			&thread->threadId);   // returns the thread identifier

		return &thread->header;
	}

	unsigned propellerGetCurrentThreadID()
	{
		return GetCurrentThreadId();
	}

}
}

#endif
