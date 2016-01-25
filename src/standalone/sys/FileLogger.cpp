// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "standalone/precompiled.h"

#include "FileLogger.h"

namespace standalone {

	FileLogger::FileLogger(const String &fileName)
	{
		outfile.open(fileName.c_str());
	}

	FileLogger::~FileLogger()
	{
		outfile.close();
	}

	void FileLogger::info(const String &msg)
	{
		outfile.write("[INFO]    ", 10);
		outfile.write(msg.c_str(), msg.size());
		outfile.write("\n", 1);
		outfile.flush();
	}

	void FileLogger::warning(const String &msg)
	{
		outfile.write("[WARNING] ", 10);
		outfile.write(msg.c_str(), msg.size());
		outfile.write("\n", 1);
		outfile.flush();
	}

	void FileLogger::error(const String &msg)
	{
		outfile.write("[ERROR]   ", 10);
		outfile.write(msg.c_str(), msg.size());
		outfile.write("\n", 1);
		outfile.flush();
	}

}