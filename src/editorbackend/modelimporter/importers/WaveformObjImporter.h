// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_WAVEFORMOBJIMOPORTER_H
#define EDITOR_WAVEFORMOBJIMOPORTER_H

#include "editorbackend/modelimporter/AbstractModelImporter.h"

namespace editor {

	class WaveformObjImporter : public AbstractModelImporter
	{
		bool convertToPropellerModel(String file, ModelStream &stream);
	};

}

#endif