// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef STANDALONE_SYS_FILELOGGER_H
#define STANDALONE_SYS_FILELOGGER_H

#include "engine/sys/Logger.h"

namespace standalone {

	class FileLogger : public engine::sys::Logger
	{
	private:
		std::ofstream outfile;

	public:
		FileLogger(const String &fileName);
		~FileLogger();

		void error(const String &msg);
		void warning(const String &msg);
		void info(const String &msg);
	};

}

#endif