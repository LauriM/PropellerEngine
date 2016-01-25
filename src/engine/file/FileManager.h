// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_FILEMANAGER_H
#define ENGINE_FILE_FILEMANAGER_H

#include <vector>

#include "engine/file/FileData.h"
#include "engine/file/Archive.h"
#include "engine/file/FileList.h"

namespace engine {
namespace file {

	class FileManager
	{
	public:
		typedef std::vector<Archive *> ArchiveList;
	private:
		ArchiveList sources;

	public:
		~FileManager();

		const bool listFiles(FileList &out) const;

		const bool addArchive(Archive *archive);

		// Open a file directly without ResourceManager, reads all the provided archives
		File openFile(const String &path);

		const ArchiveList &getArchiveList() const { return sources; }
	};

}
}

#endif
