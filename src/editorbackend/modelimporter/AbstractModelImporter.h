// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_ABSTRACTMODELIMPORTER_H
#define EDITOR_ABSTRACTMODELIMPORTER_H

#include "engine/stream/BufferedOutputStream.h"

namespace editor {

	class AbstractModelImporter
	{
	public:
		typedef engine::stream::BufferedOutputStream<engine::stream::SerializationEndian> ModelStream;

		// file - path to file to be converted
		// stream - should contain valid .PropellerModel file in a stream.
		// returns true if succeeds
		virtual bool convertToPropellerModel(String file, ModelStream &stream) = 0;
	};

}

#endif