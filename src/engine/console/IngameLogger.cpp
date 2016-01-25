// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/console/IngameLogger.h"
#include "engine/console/Console.h"

namespace engine {
namespace console {

	void IngameLogger::error(const String &msg)
	{
		Console::getHistoryList().push(String("[ERROR] ") + msg);
	}

	void IngameLogger::warning(const String &msg)
	{
		Console::getHistoryList().push(String("[WARNING] ") + msg);
	}

	void IngameLogger::info(const String &msg)
	{
		Console::getHistoryList().push(String("[INFO] ") + msg);
	}

}
}