// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_MODELIMPORTERINSTANCE_H
#define EDITOR_MODELIMPORTERINSTANCE_H

#include "editorbackend/CSharp/CSharpInstance.h"

#include "editorbackend/modelimporter/AbstractModelImporter.h"

namespace editor {

	class ModelImporterInstance : public CSharpInstance
	{
	private:
		std::vector<AbstractModelImporter*> modelImporters;

	public:
		bool init();
		void uninit();

		void import(String filename);
	};

}

#endif