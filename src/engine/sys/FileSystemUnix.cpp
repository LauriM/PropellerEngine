// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined (OS_LINUX) || defined (OS_ANDROID) || defined (OS_WEB) || defined (OS_MAC)

#include "engine/sys/FileSystem.h"

#include <dirent.h> 

namespace engine {
namespace sys {

	bool listFilesInDirectory(std::vector<String> &out, const String &path)
	{
		dirent *diren;

		DIR *dir = opendir(".");
		if (dir)
		{
			while ((diren = readdir(dir)) != NULL)
			{
				out.push_back(String(diren->d_name));
			}

			closedir(dir);

			return true;
		}

		return false;
	}

	void initializeFilesystem() { }

	bool fileOpen(FILE **file, const String &fileName, const String &mode)
	{
		(*file) = fopen(fileName.c_str(), mode.c_str());

		if(!*file)
			return false;

		return true;
	}

	void fileClose(FILE *file)
	{
		fclose(file);
	}

}
}

#endif
