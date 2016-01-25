// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/ArchiveCreator.h"

#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "engine/sys/FileSystem.h"
#include "engine/file/PropellerPackageVersion.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(ArchiveCreator);

	bool ArchiveCreator::init()
	{
		registerEvent("addFolder", this, &ArchiveCreator::addFolderToArchive);
		registerEvent("addFile", this, &ArchiveCreator::addFileToArchive);
		registerEvent("build", this, &ArchiveCreator::buildArchive);
		registerEvent("clear", this, &ArchiveCreator::clear);

		return true;
	}

	void ArchiveCreator::addFolderToArchive(const String folder)
	{
		std::vector<String> files;
		engine::sys::listFilesInDirectory(files, folder);

		DEBUG_PRINT("files: " << files.size());

		for (unsigned i = 0; i < files.size(); ++i)
			addFileToArchive(files[i]);
	}

	void ArchiveCreator::addFileToArchive(const String file)
	{
		if (file == ".")
			return;

		if (file == "..")
			return;

		files.push_back(file);
		DEBUG_PRINT("Adding " << file);
	}

	void ArchiveCreator::buildArchive(const String filename)
	{
		LOG_INFO("Building archive...");

		engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> header;
		engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> data;

		// .pp header
		header.write(PROPELLER_PACKAGE_IDENTIFIER, PROPELLER_PACKAGE_IDENTIFIER_SIZE);
		header.write(unsigned(PROPELLER_PACKAGE_VERSION_ID));
		header.write(files.size());

		unsigned bufferSize = 15000;
		char *buffer = (char*)malloc(bufferSize);

		for (unsigned i = 0; i < files.size(); ++i)
		{
			FILE *file = NULL;
			engine::sys::fileOpen(&file, "../data/" + files[i], "rb");

			if (file == NULL)
			{
				LOG_WARNING("Could not open file: " << files[i]);
				continue;
			}

			unsigned offset = data.getIndex();
			fseek(file, 0L, SEEK_END);
			unsigned size = ftell(file);
			fseek(file, 0L, SEEK_SET);

			header.write(files[i]); //filename
			header.write(offset);   //offset from data section start (first is 0)
			header.write(size);     //size

			if (size > bufferSize)
			{
				bufferSize = size;
				buffer = (char*)realloc(buffer, bufferSize);
				DEBUG_PRINT("Resizing buffer to " << bufferSize);
			}

			fread_s(buffer, bufferSize, size, 1, file);
			data.write(buffer, size);

			LOG_INFO("file " << files[i] << " written offset: " << offset << " size: " << size);
			DEBUG_PRINT("file " << files[i] << " written offset: " << offset << " size: " << size);
		}

		free(buffer);

		std::ofstream output;

		output.open(filename.c_str(), std::ios::binary);
		output.write((char*)header.getData(), header.getIndex());
		output.write((char*)data.getData(), data.getIndex());
		output.close();

		LOG_INFO("Archive build done: " << filename);
	}

	void ArchiveCreator::clear()
	{
		files.clear();
	}

}