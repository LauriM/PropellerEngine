// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/MemoryMappedFile.h"

#ifdef OS_WINDOWS

namespace engine {
namespace sys {

	MemoryMappedFile::MemoryMappedFile()
		: ptr(NULL)
		, hFile(NULL)
		, hMap(NULL)
		, fileSize(0)
	{ }

	MemoryMappedFile::MemoryMappedFile(const String &path)
		: ptr(NULL)
		, hFile(NULL)
		, hMap(NULL)
		, fileSize(0)
	{
		hFile = CreateFile(path.c_str() , GENERIC_READ, FILE_SHARE_READ , NULL, OPEN_EXISTING, 0 , NULL);

		DWORD error = GetLastError();

		if (error != 0)
		{
			//LOG_ERROR("MMF failed!");
			return;
		}

		if (hFile == NULL)
			return;

		hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

		if (hMap == NULL)
		{
			CloseHandle(hFile);
			hFile = NULL;
			return;
		}

		ptr = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

		if (ptr == NULL)
		{
			CloseHandle(hMap);
			CloseHandle(hFile);
			hFile = NULL;
			return;
		}
	}

	MemoryMappedFile::~MemoryMappedFile()
	{
		if (hFile)
		{
			UnmapViewOfFile(ptr);
			CloseHandle(hMap);
			CloseHandle(hFile);
			hFile = NULL;
		}
	}

	bool MemoryMappedFile::isMapped()
	{
		if (hFile == NULL)
			return false;

		if (hMap == NULL)
			return false;

		return true;
	}

	size_t MemoryMappedFile::getSize()
	{
		if (fileSize == 0)
			fileSize = GetFileSize(hFile, NULL);

		return fileSize;
	}

}
}

#endif
