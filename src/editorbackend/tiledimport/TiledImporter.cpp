// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/tiledimport/TiledImporter.h"
#include "engine/scene/TransformComponent.h"
#include "engine/scene/Entity.h"
#include "engine/rtti/Object.h"
#include "engine/GameInstance.h"

#include <json/json.h>
#include <boost/lexical_cast.hpp>

namespace editor {

	//TODO: custom parameters, name -> entity type! 

	void TiledImporter::importTiledFile(const String &filename, engine::GameInstance *instance)
	{
		LOG_INFO("[TiledImporter] Importing " << filename);

		Json::Value root;

		Json::Reader reader;

		std::ifstream tiledFile(filename.c_str()); //This is ok because editor is only running on windows

		reader.parse(tiledFile, root);

		tiledFile.close();

		// Root stuff
		Json::ValueIterator it = root.begin();

		Json::Value layers;
		Json::Value tilesets;
		Json::Value errorValue(TILED_LOADER_ERROR_INT);

		int version = 0;
		int width = 0;
		int height = 0;
		int tilewidth = 0;
		int tileheight = 0;

		version = root.get("version", errorValue).asInt();
		width = root.get("width", errorValue).asInt();
		height = root.get("height", errorValue).asInt();
		tilewidth = root.get("tilewidth", errorValue).asInt();
		tileheight = root.get("tileheight", errorValue).asInt();

		tilesets = root.get("tilesets", errorValue);
		layers = root.get("layers", errorValue);

		LOG_INFO("Tiled format version: " << version);
		LOG_INFO("Map size: " << width << "x" << height);

		// Basic info is now gathered, lets read the tileset information
		std::vector<String> tiles;

		for (unsigned i = 0; i < tilesets.size(); ++i)
		{
			String tilename = tilesets[i].get("name", errorValue).asString();

			tiles.push_back(tilename);
		}

		// Tile info is loaded, now lets parse the layers!

		for (unsigned i = 0; i < layers.size(); ++i)
		{
			Json::Value data = layers[i].get("data", errorValue);

			for (int x = 0; x < width; ++x)
			{
				for (int y = 0; y < height; ++y)
				{
					int val = data[x + width * y].asInt();

					if (val == 0)
						continue;

					engine::scene::Entity *entity = engine::rtti::dynamicCast<engine::scene::Entity>(engine::rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
					entity->setName("TiledTile");

					entity->setEntityType(String(tiles[val - 1]) + String(".type"));
					instance->getEntityTypeManager()->applyTypeOnEntity(entity);

					// Find the transformcomponent to position the tile correctly
					engine::scene::TransformComponent *transform = entity->findComponent<engine::scene::TransformComponent>();

					if (transform == NULL)
					{
						LOG_ERROR("TILE TYPE MISSING TRANSFORMCOMPONENT !! ABORTING! (" << tiles[val - 1] << ")");
						return;
					}

					transform->setPosition(engine::math::Vec3(float(x * tilewidth*2), float(y * tileheight*2), float(i)));
					transform->setDirection(engine::math::Vec3(0.f, 0.f, 1.f));

					instance->getScene()->addEntity(entity);
				}
			}
		}
	}

}