#ifndef ANDROIDLOGGER_H
#define ANDROIDLOGGER_H

#include "engine/sys/Logger.h"

#include <android/log.h>

#define  LOG_TAG    "PropellerEngine"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace android {

	class AndroidLogger : public engine::sys::Logger
	{
	public:
		void error(const String &msg);
		void warning(const String &msg);
		void info(const String &msg);
	};

}

#endif