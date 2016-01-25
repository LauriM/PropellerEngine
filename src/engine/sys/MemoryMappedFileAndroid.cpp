// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/MemoryMappedFile.h"

#if defined (OS_ANDROID)

namespace engine {
namespace sys {

	MemoryMappedFile::MemoryMappedFile()
		: ptr(NULL)
		, fileSize(0)
	{ }

	MemoryMappedFile::MemoryMappedFile(const String &path)
		: fileSize(0)
		, ptr(NULL)
	{ }

	MemoryMappedFile::~MemoryMappedFile() { }

	bool MemoryMappedFile::isMapped()
	{
		return false;
	}

	size_t MemoryMappedFile::getSize()
	{
		return 0;
	}

}
}

#endif
