// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/resource/ResourceManager.h"
#include "engine/resource/ResourceLoader.h"
#include "engine/console/Command.h"
#include "engine/console/Console.h"
#include "engine/GameInstance.h"

namespace command {
	CREATE_COMMAND(resourcelist, "List all resources loaded")
	{
		engine::resource::ResourceManager::ResourceReportList report;

		instance->getResourceManager()->getResourceReport(report);

		LOG_INFO("Resource list: ");

		for (unsigned i = 0; i < report.size(); ++i)
		{
			LOG_INFO("> " << report[i].name << " Ram: " << report[i].sizeRam << " GRam: " << report[i].sizeGRam);
		}

		return 0;
	}
}

namespace engine {
namespace resource {

	// Add all open resources to the list
	void ResourceManager::getResourceReport(ResourceReportList &list)
	{
		ResPairIter res = resources.begin();

		while (res != resources.end())
		{
			ResourceStat line;
			line.name = res->second->getName();
			line.sizeGRam = res->second->getGRamSize();
			line.sizeRam = res->second->getSize();

			list.push_back(line);

			++res;
		}
	}

	Resource* ResourceManager::getResourceByName(String name)
	{
		PROFILE;
		ResPairIter res = resources.find(name);

		if (res != resources.end())
		{
			//Found resource from the cache! Lets give that!
			return res->second;
		}

		//Resource was not found, lets try to load it.

		Resource *resBase = NULL;

		for(unsigned i = 0; i < resourceLoaders.size(); ++i)
		{
			// If the current resourceloader doesn't handle the filetype, jump to next one
			if (!doesResourceLoaderHandleFileByType(resourceLoaders[i], name))
				continue; 

			// Load resource
			resBase = resourceLoaders[i]->getResourceByName(name);

			if(resBase != NULL)
			{
				//Found it! Lets cache and return it.
				resources.insert(ResPair(name, resBase));

				return resBase;
			}
		}

		//Could not find even from the filemanager...
		return NULL;
	}

	void ResourceManager::addResourceLoader(ResourceLoader *loader)
	{
		resourceLoaders.push_back(loader);
	}

	ResourceManager::~ResourceManager()
	{
		for(unsigned i = 0; i < resourceLoaders.size(); ++i)
		{
			delete resourceLoaders[i];
		}
	}

	bool ResourceManager::doesResourceLoaderHandleFileByType(ResourceLoader *loader, const String &filename) const
	{
		PROFILE;

		if (filename == "")
			return false;

		unsigned dotPos = filename.find_last_of(".");

		if (dotPos == 0)
			return false;

		String fileExtension = filename.substr(dotPos, filename.length() - dotPos);

		std::vector<String> types;
		loader->getTypesHandled(types);

		for (unsigned i = 0; i < types.size(); ++i)
		{
			if (fileExtension == types[i])
				return true;
		}

		return false;
	}

	// Preparing for hibernation, removing all resources that have GPU stuff
	void ResourceManager::prepareHibernation()
	{
		ResPairIter res = resources.begin();

		while (res != resources.end())
		{
			if (res->second->hasGPUResource())
			{
				disposeResource(res->second);

				// REMOVE FROM MAP
				resources.erase(res++);
			}
			else
			{
				++res;
			}
		}
	}

	void ResourceManager::disposeResource(Resource *resource)
	{
		LOG_INFO("Disposing resource: " << resource->getName());

		for (unsigned i = 0; i < resourceLoaders.size(); ++i)
		{
			// If the current resourceloader doesn't handle the filetype, jump to next one
			if (!doesResourceLoaderHandleFileByType(resourceLoaders[i], resource->getName()))
				continue;

			// Dispose
			resourceLoaders[i]->disposeResource(resource);
		}

		//TODO: Remove from the resources map here, not in prepareHibernation();
	}

} /* namespaces */
}