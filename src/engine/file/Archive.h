// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_ARCHIVE_H
#define ENGINE_FILE_ARCHIVE_H

#include "engine/lang/ReferenceCountable.h"
#include "engine/file/FileList.h"

#include <vector>

namespace engine {
namespace file {

	class FileData;

	typedef std::string String;

	class Archive
	{
	public:
		virtual ~Archive() { }

		virtual const String getName() const = 0;

		virtual const bool canWrite() const = 0;
		virtual const bool canRead() const = 0;

		virtual bool listFiles(FileList &out) = 0;

		virtual engine::lang::ReferenceCountedPointer<FileData> openFile(const String &path) = 0;

		virtual void releaseFile(FileData *file) = 0;
	};

}
}

#endif