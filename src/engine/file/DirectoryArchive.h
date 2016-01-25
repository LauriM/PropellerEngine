// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_DIRECTORYARCHIVE_H
#define ENGINE_FILE_DIRECTORYARCHIVE_H

#include "engine/file/FileData.h"
#include "engine/file/Archive.h"
#include "engine/sys/MemoryMappedFile.h"

namespace engine {
namespace file {

	class DirectoryArchive : public Archive
	{
	private:
		String baseDir;

	public:
		DirectoryArchive(const String &path);

		bool const canWrite() const;
		bool const canRead() const;

		bool listFiles(FileList &out);

		const String getName() const { return String("DirectoryArchive").append(baseDir); }

		File openFile(const String &path);
		void releaseFile(FileData *file);
	};

}
}

#endif