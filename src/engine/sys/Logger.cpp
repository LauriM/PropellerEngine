// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/sys/Logger.h"
#include "engine/sys/Mutex.h"

namespace engine {
namespace sys {

	Logger *g_loggers[MAX_LOGGER_COUNT] = { NULL, NULL, NULL };
	Mutex *g_logMutex;

	void initLogging()
	{
		if (g_logMutex == NULL)
			g_logMutex = createMutex();
	}

	void Logger::errorProxy(const String &msg)
	{
		waitAndTakeMutex(g_logMutex);
		error(msg);
		releaseMutex(g_logMutex);
	}

	void Logger::warningProxy(const String &msg)
	{
		waitAndTakeMutex(g_logMutex);
		warning(msg);
		releaseMutex(g_logMutex);
	}

	void Logger::infoProxy(const String &msg)
	{
		waitAndTakeMutex(g_logMutex);
		info(msg);
		releaseMutex(g_logMutex);
	}

	void Logger::log(const String &group, const LogLevel level, const String &msg)
	{
		TOMBSTONE(31_5_2015);
		waitAndTakeMutex(g_logMutex);

		String output = "[" + group + "] " + msg;

		switch (level)
		{
		case LOGLEVEL_ERROR :
			error(output);
		case LOGLEVEL_WARNING:
			warning(output);
		case LOGLEVEL_INFO:
			info(output);
		default:
			break;
		}

		releaseMutex(g_logMutex);
	}

	void addLogger(Logger *logger)
	{
		for (unsigned i = 0; i < MAX_LOGGER_COUNT; ++i)
		{
			if (g_loggers[i] == NULL)
			{
				g_loggers[i] = logger;
				return;
			}
		}

		LOG_ERROR("Raise MAX_LOGGER_COUNT !! !!");
	}

}
}
