// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/DateTime.h"

#include <ctime>

namespace engine {
namespace sys {

	String getCurrentTimestampForFile()
	{
		time_t time = std::time(0);
		struct tm *now = localtime(&time);

		String timestamp;

		std::stringstream ss;

		ss << now->tm_year + 1900;
		ss << "_";
		ss << now->tm_mon + 1;
		ss << "_";
		ss << now->tm_mday;
		ss << "_";
		ss << now->tm_hour;
		ss << "_";
		ss << now->tm_min;
		ss << "_";
		ss << now->tm_sec;

		return ss.str();
	}

}
}
