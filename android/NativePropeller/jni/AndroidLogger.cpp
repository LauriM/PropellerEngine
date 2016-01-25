#include "engine/precompiled.h"

#include "AndroidLogger.h"

namespace android {

	void AndroidLogger::info(const String &msg)
	{
		LOGI("[INFO] %s\n", msg.c_str());
	}

	void AndroidLogger::warning(const String &msg)
	{
		LOGI("[WARNING] %s\n", msg.c_str());
	}

	void AndroidLogger::error(const String &msg)
	{
		LOGE("[ERROR] %s\n", msg.c_str());
	}

}
