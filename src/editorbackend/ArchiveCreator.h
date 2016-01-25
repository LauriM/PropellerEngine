// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_ARCHIVECREATOR_H
#define EDITOR_ARCHIVECREATOR_H

#include "editorbackend/CSharp/CSharpInstance.h"

namespace editor {

	class ArchiveCreator : public CSharpInstance
	{
	private:
		std::vector<String> files;

	public:
		bool init();
		void uninit() {}

		void addFolderToArchive(const String folder);
		void addFileToArchive(const String file);
		void buildArchive(const String filename);

		// clear the archive to build a new one
		void clear();
	};

}

#endif