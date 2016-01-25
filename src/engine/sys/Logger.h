// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYS_LOGGING_H
#define ENGINE_SYS_LOGGING_H

#include "engine/preprocessor/shared.h"

#define HANDLE_MESSAGE(p_msg)\
	String output;\
	std::stringstream __stringStream__; \
	__stringStream__ << p_msg; \
	output = __stringStream__.str();

// current logging commands
#define LOG_INFO(p_msg) do { HANDLE_MESSAGE(p_msg); for(unsigned i = 0; i < engine::sys::MAX_LOGGER_COUNT; ++i) { if(engine::sys::g_loggers[i] != NULL) {  engine::sys::g_loggers[i]->infoProxy(output); } } } while (false)
#define LOG_WARNING(p_msg) do { HANDLE_MESSAGE(p_msg); for(unsigned i = 0; i < engine::sys::MAX_LOGGER_COUNT; ++i) { if(engine::sys::g_loggers[i] != NULL) { engine::sys::g_loggers[i]->warningProxy(output); } } } while (false)
#define LOG_ERROR(p_msg) do { HANDLE_MESSAGE(p_msg); for(unsigned i = 0; i < engine::sys::MAX_LOGGER_COUNT; ++i) { if(engine::sys::g_loggers[i] != NULL) {  engine::sys::g_loggers[i]->errorProxy(output); } } } while (false)

enum LogLevel
{
	LOGLEVEL_ERROR = 0,
	LOGLEVEL_WARNING,
	LOGLEVEL_INFO,
};

namespace engine {
namespace sys {

	struct Mutex;

	const unsigned MAX_LOGGER_COUNT = 3;

	void initLogging();

	class Logger {
	public:
		void errorProxy(const String &msg);
		void warningProxy(const String &msg);
		void infoProxy(const String &msg);

		virtual void error(const String &msg) = 0;
		virtual void warning(const String &msg) = 0;
		virtual void info(const String &msg) = 0;

		void log(const String &group, const LogLevel level, const String &msg);
	};

	extern Logger *g_loggers[MAX_LOGGER_COUNT];
	extern Mutex *g_logMutex;

	void addLogger(Logger *logger);

}
}

#endif