// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined(OS_LINUX) || defined(OS_ANDROID)

#include "engine/sys/Atomic.h"

namespace engine {
namespace sys {

	void AtomicIncrement(volatile unsigned *value)
	{
		__sync_fetch_and_add(value, 1);
	}

	void AtomicDecrement(volatile unsigned *value)
	{
		__sync_fetch_and_sub(value, 1);
	}

}
}

#endif
