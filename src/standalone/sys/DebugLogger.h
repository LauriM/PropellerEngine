// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_SYS_DEBUGLOGGER_H
#define GAME_SYS_DEBUGLOGGER_H

#include "engine/sys/Logger.h"

namespace game {
namespace sys {

	class DebugLogger : public engine::sys::Logger
	{
	public:
		void error(const String &msg);
		void warning(const String &msg);
		void info(const String &msg);
	};

}
}

#endif