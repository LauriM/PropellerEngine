// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "standalone/precompiled.h"
#include "standalone/sys/DebugLogger.h"

namespace game {
namespace sys {

	void DebugLogger::error(const String &msg)
	{
		DEBUG_PRINT("[ERROR]   " << msg);
		printf("[ERROR]   %s\n", msg.c_str());
	}

	void DebugLogger::warning(const String &msg)
	{
		DEBUG_PRINT("[WARNING] " << msg);
		printf("[WARNING] %s\n", msg.c_str());
	}

	void DebugLogger::info(const String &msg)
	{
		DEBUG_PRINT("[INFO]    " << msg);
		printf("[INFO]    %s\n", msg.c_str());
	}

}
}