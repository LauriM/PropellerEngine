// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/preprocessor/platform.h"

#ifdef OS_WINDOWS

#include "engine/precompiled.h"

#include <vector>
#include <Windows.h>

#include "engine/sys/FileSystem.h"

namespace engine {
namespace sys {

	bool listFilesInDirectory(std::vector<String> &out, const String &path)
	{
		WIN32_FIND_DATA ffd;
		HANDLE hFile = INVALID_HANDLE_VALUE;
		DWORD dwError=0;
		String szDir;

		szDir.reserve(path.size() + 2);
		szDir = path;
		szDir += "\\*";

		hFile = FindFirstFile(szDir.c_str(), &ffd);

		while(FindNextFile(hFile, &ffd) != 0)
		{
			out.push_back(ffd.cFileName);
		}

		return true;
	}

	void initializeFilesystem() { }

	bool fileOpen(FILE **file, const String &fileName, const String &mode)
	{
		errno_t err = fopen_s(file, fileName.c_str(), mode.c_str());

		if (err == 0)
			return true;

		return false;
	}

	void fileClose(FILE *file)
	{
		fclose(file);
	}

}
}

#endif
