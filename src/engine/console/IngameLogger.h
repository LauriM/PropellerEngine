// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_CONSOLE_IMGAMELOGGER_H
#define ENGINE_CONSOLE_IMGAMELOGGER_H

#include "engine/sys/Logger.h"

namespace engine {
namespace console {

	class IngameLogger : public sys::Logger
	{
		void error(const String &msg);
		void warning(const String &msg);
		void info(const String &msg);
	};

}
}

#endif