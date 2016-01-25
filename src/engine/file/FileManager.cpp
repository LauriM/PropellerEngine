// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/file/FileManager.h"
#include "engine/file/FileData.h"
#include "engine/console/Console.h"
#include "engine/GameInstance.h"
#include "engine/console/Command.h"

namespace command {

	CREATE_COMMAND(filemanagerlist, "List all Archives loaded") // list filemanager sources
	{
		const engine::file::FileManager::ArchiveList sources = instance->getFileManager()->getArchiveList();

		for(unsigned i = 0; i < sources.size(); ++i)
			LOG_INFO(" >> " << sources[i]->getName());

		return 0;
	}

}

namespace engine {
namespace file {

	const bool FileManager::listFiles(FileList &out) const
	{
		PROFILE;

		for(unsigned int i = 0; i < sources.size(); ++i)
		{
			sources[i]->listFiles(out);
		}

		return true;
	}

	const bool FileManager::addArchive(Archive *archive)
	{
		sources.insert(sources.begin(), archive);

		return true;
	}

	File FileManager::openFile(const String &path)
	{
		PROFILE;

		LOG_INFO("[FileManager] openFile " << path);

		for (unsigned int i = 0; i < sources.size(); ++i)
		{
			File file = sources[i]->openFile(path);

			if (file.isValid())
			{
				return file;
			}
		}

		return File(); // could not find the file
	}

	FileManager::~FileManager()
	{
		for(unsigned i = 0; i < sources.size(); ++i)
		{
			delete sources[i];
		}
	}

}
}