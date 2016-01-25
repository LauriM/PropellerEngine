// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_FILE_PACKAGEARCHIVE_H
#define ENGINE_FILE_PACKAGEARCHIVE_H

#include "engine/file/FileData.h"
#include "engine/file/Archive.h"

#include <boost/unordered_map.hpp>

PROPELLER_FORWARD_DECLARE_2(engine, sys, MemoryMappedFile);

namespace engine {
namespace file {

	class PackageArchive : public Archive
	{
	private:
		struct FileInfo
		{
			String name;
			unsigned offset;
			unsigned size;
		};

	public:
		typedef boost::unordered_map<String, FileInfo> FileInfoList;

	private:
		// Info of a single file inside the package.
		String path;
		sys::MemoryMappedFile *mmf; 

		unsigned dataOffset;

		FileInfoList fileInfos;

	public:
		PackageArchive(const String &pathToPackage);
		~PackageArchive();

		bool const canWrite() const;
		bool const canRead() const;

		bool listFiles(FileList &out);
		
		const String getName() const { return String("DirectoryArchive").append(path); }

		File openFile(const String &path);
		void releaseFile(FileData *file);
	};

}
}

#endif