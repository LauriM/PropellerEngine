// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/file/PackageArchive.h"
#include "engine/file/FileData.h"
#include "engine/sys/FileSystem.h"
#include "engine/sys/MemoryMappedFile.h"
#include "engine/stream/InputStream.h"
#include "engine/file/PropellerPackageVersion.h"

namespace engine {
namespace file {

	PackageArchive::PackageArchive(const String &pathToPackage)
		: path(pathToPackage)
	{
		PROFILE;

		//  Open the package
		mmf = new sys::MemoryMappedFile(pathToPackage);

		if (mmf->getPointer() == NULL)
		{
			LOG_WARNING("Could not open package: " << pathToPackage);
			return;
		}

		stream::InputStream<stream::SerializationEndian> inputStream(mmf->getPointer());

		unsigned fileCount;

		char versionIdentifier[sizeof(PROPELLER_PACKAGE_IDENTIFIER)];
		inputStream.read(versionIdentifier, PROPELLER_PACKAGE_IDENTIFIER_SIZE);

		char correctIdentifier[] = PROPELLER_PACKAGE_IDENTIFIER;

		if (String(versionIdentifier).substr(0, PROPELLER_PACKAGE_IDENTIFIER_SIZE) != String(PROPELLER_PACKAGE_IDENTIFIER).substr(0, PROPELLER_PACKAGE_IDENTIFIER_SIZE))
		{
			LOG_WARNING(pathToPackage << " is not a valid PropellerPackage!");
			return;
		}

		unsigned version;

		inputStream.read(version);

		if (version != 1)
		{
			LOG_WARNING(pathToPackage << " invalid package version!");
			return;
		}

		inputStream.read(fileCount);

		LOG_INFO("[PackageArchive] Opening package " << pathToPackage << " with " << fileCount << " files");

		for (unsigned i = 0; i < fileCount; ++i)
		{
			FileInfo info;

			inputStream.read(info.name);
			inputStream.read(info.offset);
			inputStream.read(info.size);

			fileInfos.insert(FileInfoList::value_type(info.name, info));
		}

		dataOffset = inputStream.getIndex();
	}

	PackageArchive::~PackageArchive()
	{
		delete mmf;
	}

	const bool PackageArchive::canWrite() const
	{
		return false;
	}

	const bool PackageArchive::canRead() const
	{
		return true;
	}

	bool PackageArchive::listFiles(FileList &out)
	{
		PROFILE;

		FileInfoList::iterator it = fileInfos.begin();

		while (it != fileInfos.end())
		{
			out.addFile(it->second.name);
			++it;
		}

		return false;
	}

	File PackageArchive::openFile(const String &path)
	{
		PROFILE;

		FileInfoList::iterator it = fileInfos.find(path);

		if (it == fileInfos.end())
			return File(); // file is not in this archive!

		const FileInfo info = it->second;

		return File(new FileData((char*)mmf->getPointer() + info.offset + dataOffset, info.size, this));
	}

	void PackageArchive::releaseFile(FileData *file)
	{
		// no need to release the file, the filedata is refcounted, should be removed
		// the actual data itself is in one mmf thats owned by the PackageArchive
	}

}
}