// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYSTEMMANAGER_H
#define ENGINE_SYSTEMMANAGER_H

PROPELLER_FORWARD_DECLARE_1(engine, SystemBase);
PROPELLER_FORWARD_DECLARE_2(engine, rtti, Class);

#include <vector>

namespace engine {

	class SystemManager
	{
	public:
		typedef std::vector<SystemBase*> SystemList;

	private:
		SystemList systems;

		void sortByWeight();

		bool paused;

	public:
		SystemManager();

		// Weight is used to order the systems during runtime
		bool addSystem(SystemBase *system, int weight);

		void updateSystems(float delta);
		void renderFrame();

		void shutdown();

		void stopSystem(const String &systemName);

		const SystemList& getSystemList() const { return systems; }

		// is the game paused?
		bool isPaused() const { return paused; }
		void setPaused(bool p) { paused = p; }

		void togglePaused()
		{
			if (paused)
				paused = false;
			else
				paused = true;
		}
	};

}

#endif