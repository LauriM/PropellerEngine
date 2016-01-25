// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYS_THREAD_H
#define ENGINE_SYS_THREAD_H

#if defined (OS_WINDOWS) || defined (OS_LINUX)
#define PROPELLER_TLS __declspec(thread)
#endif

#if defined (OS_ANDROID)
#define PROPELLER_TLS __thread
#endif

namespace engine {
namespace sys {

	struct Thread
	{
		String name;
		bool running;
		void (*entryPoint)(void*);
		void *userData;
	};

	Thread *propellerCreateThread(String name, void(*entryPoint)(void *), void *userData);

	unsigned propellerGetCurrentThreadID();
}
}

#endif
