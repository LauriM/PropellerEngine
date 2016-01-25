// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_PROPELLERMODELLOADER_H
#define ENGINE_RENDERER_PROPELLERMODELLOADER_H

#include "engine/resource/ResourceLoader.h"
#include "engine/file/FileManager.h"

PROPELLER_FORWARD_DECLARE_2(engine, renderer, RendererSystem);

namespace engine {
namespace renderer {

	class PropellerModelLoader : public resource::ResourceLoader
	{
	private:
		RendererSystem *rendererSystem;

	public:
		PropellerModelLoader(engine::file::FileManager *fileManager, RendererSystem *rendererSystem)
			: resource::ResourceLoader(fileManager)
			, rendererSystem(rendererSystem)
		{ }

		resource::Resource *getResourceByName(const String &name);

		void getTypesHandled(std::vector<String> &typesHandled);

		void disposeResource(resource::Resource *resource);
	private:

		resource::Resource *loadModelVersion1(stream::InputStream<stream::SerializationEndian> &inputStream);
		resource::Resource *loadModelVersion2(stream::InputStream<stream::SerializationEndian> &inputStream);
	};

}
}
#endif
