// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYS_MUTEX_H
#define ENGINE_SYS_MUTEX_H

namespace engine {
namespace sys {

	struct Mutex;

	Mutex *createMutex();
	void waitAndTakeMutex(Mutex *mutex);
	void releaseMutex(Mutex *mutex);

}
}

#endif