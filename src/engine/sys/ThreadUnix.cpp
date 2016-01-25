// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined(OS_LINUX) || defined(OS_ANDROID)

#include "engine/sys/Thread.h"

#include <pthread.h>

namespace engine {
namespace sys {

	struct UnixThread
	{
		Thread header;

		pthread_t thread;
	};

	void *unixThreadEntryPoint(void *param)
	{
		UnixThread *t = (UnixThread*)param;

		LOG_INFO(">> [Thread] Starting: " << t->header.name);

		t->header.entryPoint(t->header.userData);

		LOG_INFO(">> [Thread] Finished: " << t->header.name);

		t->header.running = false;

		return NULL;
	}

	Thread *propellerCreateThread(String name, void(*entryPoint)(void *), void *userData)
	{
		UnixThread *thread = new UnixThread();
		thread->header.name = name;
		thread->header.running = true;
		thread->header.entryPoint = entryPoint;
		thread->header.userData = userData;

		//TODO: error check
		pthread_create(&thread->thread, NULL, &unixThreadEntryPoint, thread);

		return &thread->header;
	}

	unsigned propellerGetCurrentThreadID()
	{
		return pthread_self();
	}

}
}

#endif
