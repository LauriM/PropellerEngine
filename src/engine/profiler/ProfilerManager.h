// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PROFILER_PROFILERMANAGER_H
#define ENGINE_PROFILER_PROFILERMANAGER_H

#include <time.h>
#include <vector>
#include "engine/sys/Thread.h"
#include "engine/util/Array.h"

PROPELLER_FORWARD_DECLARE_1(Json, Value);

namespace engine {
namespace profiler {

	// all times handles as microseconds (stored in longs)

	class ProfilerManager;

	extern PROPELLER_TLS ProfilerManager *g_profilerManager;
	extern util::Array<ProfilerManager*> g_profilerManagers; // used to find all managers across all threads

	struct Profile
	{
		Profile(const char *name, Profile *parentNode)
			: name(name)
			, parentNode(parentNode)
			, calls(0)
			, totalTime(0)
			, lastTime(0)
		{ }

		const char *name;
		Profile *parentNode;
		std::vector<Profile*> childs;

		// Stats
		unsigned calls;
		long totalTime;
		long lastTime;
	};


	class ProfilerManager
	{
	private:
		Profile *rootNode;
		Profile *currentNode;

		void generateReport(std::vector<String> &lines);
		void addChildsToReport(std::vector<String> &lines, Profile *node, unsigned depth);

		void cleanUpChilds(Profile *node);

	public:
		ProfilerManager();
		~ProfilerManager();

		void profileStart(const char *name);
		void profileEnd(long time);

		void outputToStdio();
		void outputToLog();

		// Dump the current profiler contents into disk as json
		void addChildsToJSON(Profile *node, Json::Value &value);

		Profile *getRootNode();

		void dumpProfilerAsJSON();
	};

}
}

#endif