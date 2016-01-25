// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_MEMORYMAPPEDFILE_H
#define ENGINE_FILE_MEMORYMAPPEDFILE_H

namespace engine {
namespace sys {

	class MemoryMappedFile
	{
	private:
		void *ptr;
		size_t fileSize;

#if defined (OS_WINDOWS)
		HANDLE hFile;
		HANDLE hMap;
#endif
#if defined (OS_LINUX) || defined (OS_WEB) || defined (OS_MAC) 
		int file;
#else
	//#error "UNSUPPORTED PLATFORM"
#endif

	public:
		MemoryMappedFile();
		MemoryMappedFile(const String &path);
		~MemoryMappedFile();

		bool isMapped();

		inline void *getPointer()
		{
			return ptr;
		}

		size_t getSize();

	};

}
}

#endif
