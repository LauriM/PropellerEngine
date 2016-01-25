// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/MemoryMappedFile.h"

#if defined (OS_LINUX) || defined (OS_WEB) || defined (OS_MAC) 

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

namespace engine {
namespace sys {

	MemoryMappedFile::MemoryMappedFile()
		: ptr(NULL)
		, fileSize(0)
		, file(NULL)
	{}

	MemoryMappedFile::MemoryMappedFile(const String &path)
		: fileSize(0)
		, ptr(NULL)
		, file(0)
	{
		FILE *f = fopen(path.c_str(), "rb");

		if (f == NULL)
			return;

		fseek(f, 0L, SEEK_END);
		fileSize = ftell(f);
		fclose(f);

		file = open (path.c_str(), O_RDWR, S_IRUSR | S_IWUSR);

		ptr = mmap (0, fileSize, PROT_READ, MAP_SHARED, file, 0); 
		close (file); 
	}

	MemoryMappedFile::~MemoryMappedFile()
	{
		if(ptr != NULL)
			munmap (ptr, fileSize);  
	}

	bool MemoryMappedFile::isMapped()
	{
		return ptr != NULL;
	}

	size_t MemoryMappedFile::getSize()
	{
		return fileSize;
	}

}
}

#endif
