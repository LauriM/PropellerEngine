// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_TEXTURELOADER_H
#define ENGINE_RENDERER_TEXTURELOADER_H

#include "engine/resource/ResourceLoader.h"
#include "engine/renderer/TextureResource.h"

PROPELLER_FORWARD_DECLARE_2(engine, file, FileManager);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, RendererSystem);

namespace engine {
namespace renderer {

	class TextureLoader : public resource::ResourceLoader
	{
	private:
		RendererSystem *rendererSystem;

	public:
		TextureLoader(engine::file::FileManager *fileManager, RendererSystem *rendererSystem)
			: resource::ResourceLoader(fileManager)
			, rendererSystem(rendererSystem)
		{ }

		resource::Resource *getResourceByName(const String &name);

		void getTypesHandled(std::vector<String> &typesHandled);

		void disposeResource(resource::Resource *resource);

	private:
		resource::Resource *handlePNG(const String &name);
		resource::Resource *handleDDS(const String &name);
	};

}
}

#endif
