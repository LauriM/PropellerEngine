// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined (OS_LINUX) || defined(OS_ANDROID)

#include "engine/sys/Sleep.h"

namespace engine {
namespace sys {

	void propellerSleep(unsigned ms)
	{
		usleep(ms);
	}

}
}

#endif
