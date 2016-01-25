// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined (OS_WINDOWS)

#include "engine/sys/Sleep.h"

namespace engine {
namespace sys {

	void propellerSleep(unsigned ms)
	{
		Sleep(ms);
	}

}
}

#endif
