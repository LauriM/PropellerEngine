// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined(OS_WINDOWS)

#include "engine/sys/Atomic.h"

namespace engine {
namespace sys {

	void AtomicIncrement(volatile unsigned *value)
	{
		InterlockedIncrement(value);
	}

	void AtomicDecrement(volatile unsigned *value)
	{
		InterlockedDecrement(value);
	}

}
}

#endif