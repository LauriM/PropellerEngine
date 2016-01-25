// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/SystemManager.h"

#include "engine/rtti/Object.h"
#include "engine/rtti/RTTI.h"
#include "engine/GameInstance.h"
#include "engine/SystemBase.h"
#include "engine/console/Cvar.h"
#include "engine/console/Console.h"
#include "engine/console/Command.h"

#include <algorithm>
namespace cvar {
	EXTERN_CVAR(int, developer);
}

namespace command {
	CREATE_COMMAND(systemlist, "List all subsystems in the engine")
	{
		const engine::SystemManager::SystemList systemList = instance->getSystemManager()->getSystemList();

		LOG_INFO("-- System list, > running, # stopped");

		String running;
		String gameplay;

		for (unsigned i = 0; i < systemList.size(); i++)
		{

			if (systemList[i]->isRunning())
				running = "> ";
			else
				running = "# ";

			if (systemList[i]->isGameplaySystem())
				gameplay = "(gameplay system)";
			else
				gameplay = "";

			LOG_INFO(running << systemList[i]->getName() << " Weight: " << systemList[i]->getWeight() << " " << gameplay);
		}

		LOG_INFO("Total of " << systemList.size() << " systems.");

		return 0;
	}

	CREATE_COMMAND(systemstart, "systemstart <system> - Start specific subsystem")
	{
		if (!*cvar::developer)
		{
			LOG_WARNING("Developer mode not enabled!");
			return -1;
		}

		if (args->size() < 2)
		{
			LOG_WARNING("Not enough parameters!");
			return -2;
		}

		String systemName = args->at(1);

		const engine::SystemManager::SystemList systemList = instance->getSystemManager()->getSystemList();

		for (unsigned i = 0; i < systemList.size(); i++)
		{
			if (systemList[i]->getName() == systemName)
			{
				systemList[i]->start();
				LOG_INFO(systemList[i]->getName() << " started");
				return 0;
			}
		}

		LOG_WARNING("System not found!");
		return -3;
	}

	CREATE_COMMAND(systemstop, "systemstop <system> - Stop specific subsystem")
	{
		if (!*cvar::developer)
		{
			LOG_WARNING("Developer mode not enabled!");
			return -1;
		}

		if (args->size() < 2)
		{
			LOG_WARNING("Not enough parameters!");
			return -2;
		}

		String systemName = args->at(1);

		const engine::SystemManager::SystemList systemList = instance->getSystemManager()->getSystemList();

		for (unsigned i = 0; i < systemList.size(); i++)
		{
			if (systemList[i]->getName() == systemName)
			{
				systemList[i]->stop();
				LOG_INFO(systemList[i]->getName() << " stopped");
				return 0;
			}
		}

		LOG_WARNING("System not found!");
		return -3;
	}
}

namespace engine {

	SystemManager::SystemManager()
		: paused(false)
	{ }

	bool SystemManager::addSystem(SystemBase *system, int weight)
	{
		PROFILE;
		system->start(); // By default the system is running, init may cancel that if needed.

		if (!system->init())
		{
			LOG_ERROR("[SystemManager] Failed to initialize system " << system->getName());
			return false;
		}

		system->setWeight(weight);

		systems.push_back(system);

		sortByWeight();

		LOG_INFO("[SystemManager]" << system->getName() << " registered");

		return true;
	}

	void SystemManager::updateSystems(float delta)
	{
		PROFILE;

		//TODO consider removing the pausing state and using the rendering
		if (paused)
		{
			for (unsigned i = 0; i < systems.size(); ++i)
			{
				if (!systems[i]->isGameplaySystem() && !systems[i]->isRendererSystem())
					systems[i]->update(delta);
			}

			return;
		}

		for (unsigned i = 0; i < systems.size(); ++i)
			if (!systems[i]->isRendererSystem())
				systems[i]->update(delta);
	}

	void SystemManager::renderFrame()
	{
		PROFILE;

		// pausing doesn't matter here!

		// update all renderer systems
		for (unsigned i = 0; i < systems.size(); ++i)
			if (systems[i]->isRendererSystem())
				systems[i]->update(0.0f);
	}

	void SystemManager::stopSystem(const String &systemName)
	{
		PROFILE;
		for (unsigned i = 0; i < systems.size(); ++i)
		{
			if (systems[i]->getName() != systemName)
				continue;

			systems[i]->stop();
			return;
		}
	}

	namespace helper {
		bool compareSystemWeight(SystemBase *x, SystemBase *y)
		{
			return (x->getWeight() < y->getWeight());
		}
	}

	void SystemManager::sortByWeight()
	{
		PROFILE;
		std::sort(systems.begin(), systems.end(), helper::compareSystemWeight);
	}

	void SystemManager::shutdown()
	{
		PROFILE;
		for (unsigned i = 0; i < systems.size(); ++i)
		{
			systems[i]->uninit();
			// no need to delete, the systems are owned by gameinstance
		}

		systems.clear();
	}

}
