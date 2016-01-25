// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_SHADERLOADER_H
#define ENGINE_RENDERER_SHADERLOADER_H

#include "engine/resource/ResourceLoader.h"
#include "engine/renderer/ShaderResource.h"

PROPELLER_FORWARD_DECLARE_2(engine, renderer, RendererSystem);

namespace engine {
namespace renderer {

	class ShaderLoader : public resource::ResourceLoader
	{
	private:
		RendererSystem *rendererSystem;

	public:
		ShaderLoader(engine::file::FileManager *fileManager, RendererSystem *rendererSystem)
			: resource::ResourceLoader(fileManager)
			, rendererSystem(rendererSystem)
		{ }

		void getTypesHandled(std::vector<String> &typesHandled);

		resource::Resource *getResourceByName(const String &name);

		void disposeResource(resource::Resource *resource);
	};

}
}

#endif