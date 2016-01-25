// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_TILEDIMPORTER_H
#define EDITOR_TILEDIMPORTER_H

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance)

namespace editor {

	class TiledImporter
	{
	public:
		static void importTiledFile(const String &filename, engine::GameInstance *instance);

		static const int TILED_LOADER_ERROR_INT = 1337;
	};

}

#endif