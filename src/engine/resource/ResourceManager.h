// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_RESOURCEMANAGER_H
#define ENGINE_RENDERER_RESOURCEMANAGER_H

#include <vector>

#include "engine/resource/Resource.h"
#include "engine/resource/ResourceLoader.h"

namespace engine {
namespace resource {

	struct ResourceStat
	{
		String name;
		size_t sizeRam;
		size_t sizeGRam;
	};

	class ResourceManager
	{
	public:
		typedef std::vector<ResourceStat> ResourceReportList;

	private:
		typedef boost::unordered_map<String, Resource *> ResourceMap;
		typedef std::pair<String, Resource *> ResPair;
		typedef ResourceMap::iterator ResPairIter;

		ResourceMap resources;

		std::vector<ResourceLoader*> resourceLoaders;

	public:
		~ResourceManager();
		Resource *getResourceByName(String name);

		void addResourceLoader(ResourceLoader *loader);

		void getResourceReport(ResourceReportList &list);

		// Prepare for hibernation, free all GPU bound assets!
		void prepareHibernation();

		// Dispose resource, remove it from the memory
		void disposeResource(Resource *resource);

	private:
		bool doesResourceLoaderHandleFileByType(ResourceLoader *loader, const String &filename) const;
	};

} /* namespaces */
}

#endif