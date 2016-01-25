// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined (OS_LINUX) || defined(OS_ANDROID)

#include "engine/sys/Mutex.h"

namespace engine {
namespace sys {

	//TODO: QQQ HACK MOVE THIS HACK AWAY
	struct timespec g_lockWait;

	struct Mutex
	{
		pthread_mutex_t mutex;
	};

	Mutex *createMutex()
	{
		Mutex *mutex = new Mutex();

		pthread_mutex_init(&mutex->mutex, NULL);
		//TODO: check if mutex is ok

		g_lockWait.tv_sec = 666;

		return mutex;
	}

	void waitAndTakeMutex(Mutex *mutex)
	{
#ifndef OS_ANDROID
		pthread_mutex_timedlock(&mutex->mutex, &g_lockWait);
#else
		pthread_mutex_lock(&mutex->mutex);
#endif
	}

	void releaseMutex(Mutex *mutex)
	{
		pthread_mutex_unlock(&mutex->mutex);
	}

}
}

#endif
