// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined (OS_WINDOWS)

#include "engine/sys/Mutex.h"

namespace engine {
namespace sys {

	struct Mutex
	{
		HANDLE mutex;
	};

	Mutex *createMutex()
	{
		Mutex *mutex = new Mutex();

		mutex->mutex = CreateMutex(NULL, FALSE, NULL);

		return mutex;
	}

	void waitAndTakeMutex(Mutex *mutex)
	{
		HRESULT res = WaitForSingleObject(mutex->mutex, INFINITE);

		if (res != WAIT_OBJECT_0)
			LOG_WARNING("[Mutex] wait failed!");
	}

	void releaseMutex(Mutex *mutex)
	{
		ReleaseMutex(mutex->mutex);
	}

}
}

#endif
