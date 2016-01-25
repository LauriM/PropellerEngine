// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/FileSystem.h"
#include "engine/file/DirectoryArchive.h"

namespace engine {
namespace file {

	struct DirectoryFile
	{
		FileData fileData;
		sys::MemoryMappedFile mmf;
	};

	DirectoryArchive::DirectoryArchive(const String &path)
		: baseDir(path)
	{
		LOG_INFO("DirectoryArchive (" << path << ")");
	}

	const bool DirectoryArchive::canWrite() const
	{
		return false;
	}

	const bool DirectoryArchive::canRead() const
	{
		return true;
	}

	bool DirectoryArchive::listFiles(FileList &out)
	{
		PROFILE;

		std::vector<String> files;
		engine::sys::listFilesInDirectory(files, baseDir);

		for (unsigned i = 0; i < files.size(); ++i)
			out.addFile(files[i]);

		return false;
	}

	File DirectoryArchive::openFile(const String &path)
	{
		PROFILE;

		DirectoryFile *dirFile = (DirectoryFile *)malloc(sizeof (DirectoryFile));

		if (dirFile == NULL)
			return File(); //empty file

		new(&dirFile->mmf) sys::MemoryMappedFile(baseDir + path);

		if (dirFile == NULL)
			return File(); //empty file

		if (dirFile->mmf.getPointer() == NULL)
		{
			// Mapping failed, file not found! Cleanup and return empty file
			dirFile->mmf.~MemoryMappedFile();
			return File();
		}
		new(&dirFile->fileData) FileData(dirFile->mmf.getPointer(), dirFile->mmf.getSize(), this);

		LOG_INFO("DirectoryArchive -> openFile " << path);

		return File(&dirFile->fileData);
	}

	void DirectoryArchive::releaseFile(FileData *file)
	{
		DirectoryFile *dirFile = (DirectoryFile*)file;

		dirFile->fileData.~FileData();
		dirFile->mmf.~MemoryMappedFile();

		free(dirFile);
	}

}
}
