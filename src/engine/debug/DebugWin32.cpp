// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/debug/Debug.h"

#ifdef OS_WINDOWS

namespace engine {
namespace debug {

	void debugPrint(const String &p_msg)
	{
		OutputDebugString(p_msg.c_str());
		OutputDebugString("\n");
	}

	void debugBreakpoint()
	{
		__debugbreak();
	}

}
}

#endif
