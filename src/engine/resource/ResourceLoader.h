// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RESOURCE_RESOURCELOADER_H
#define ENGINE_RESOURCE_RESOURCELOADER_H

#include "engine/file/FileManager.h"
#include "engine/resource/Resource.h"

namespace engine {
namespace resource {

	class ResourceLoader
	{
	protected:
		engine::file::FileManager *fileManager;

	public:
		ResourceLoader(engine::file::FileManager *fileManager)
			: fileManager(fileManager)
		{}

		virtual ~ResourceLoader() { }

		virtual void getTypesHandled(std::vector<String> &typesHandled) = 0;

		virtual resource::Resource *getResourceByName(const String &name) = 0;

		virtual void disposeResource(resource::Resource *resource) = 0;
	};

}
}


#endif