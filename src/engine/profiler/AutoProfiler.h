// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PROFILER_AUTOPROFILER_H
#define ENGINE_PROFILER_AUTOPROFILER_H

#include "engine/profiler/ProfilerManager.h"
#include "engine/sys/Timer.h"

#define PROPELLER_FUNCTION __FUNCTION__

#define PROFILE engine::profiler::AutoProfile profiler( PROPELLER_FUNCTION );

namespace engine {
namespace profiler {

	class AutoProfile
	{
	private:
		sys::Timer timer;

	public:
		AutoProfile(const char *name)
		{
			timer.start();

			if (engine::profiler::g_profilerManager == NULL)
			{
				engine::profiler::g_profilerManager = new engine::profiler::ProfilerManager();
				engine::profiler::g_profilerManagers.push(engine::profiler::g_profilerManager);
			}

			engine::profiler::g_profilerManager->profileStart(name);
		}

		~AutoProfile()
		{
			timer.stop();

			long timing = timer.getTimeInMicroSeconds();

			// Insert into the profilerManager
			engine::profiler::g_profilerManager->profileEnd(timing);
		}
	};

}
}

#endif
