// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "editorbackend/modelimporter/ModelImporterInstance.h"

#include "editorbackend/modelimporter/importers/WaveformObjImporter.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(ModelImporterInstance);

	bool ModelImporterInstance::init()
	{
		modelImporters.push_back(new WaveformObjImporter());

		registerEvent("import", this, &ModelImporterInstance::import);

		return true;
	}

	void ModelImporterInstance::uninit()
	{
		for (unsigned i = 0; i < modelImporters.size(); ++i)
			delete modelImporters[i];
	}

	void ModelImporterInstance::import(String filename)
	{
		LOG_WARNING("The importer doesn't check type of the file! Assuming waveform.");

		engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> stream;

		if (modelImporters[0]->convertToPropellerModel(filename, stream))
		{
			std::ofstream output;

			unsigned pos = filename.find_last_of("\\");
			String name = filename.substr(pos + 1);
			name = name.replace(name.find(".obj"), sizeof(".PropellerModel")-1, ".PropellerModel");

			output.open("../data/" + name, std::ios::binary);
			output.write((char*)stream.getData(), stream.getIndex());
			output.close();

			// Notify the C# instance that the archive browser should be refreshed!

			//TODO: enable and fix archive refreshing automatically here! -> crashes when enabled
			//call("requestArchiveRefresh");
		}
		else
		{
			LOG_WARNING("Importing model " << filename << " failed!");
		}
	}

}