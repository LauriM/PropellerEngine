// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/profiler/ProfilerManager.h"

#include "engine/console/Command.h"
#include "engine/console/Console.h"
#include "engine/sys/FileSystem.h"
#include "engine/sys/DateTime.h"
#include "engine/sys/Thread.h"
#include "engine/util/Array.h"
#include <json/json.h>

namespace command {

	CREATE_COMMAND(stats, "Dump profiler information to log")
	{
		engine::profiler::g_profilerManager->outputToLog();

		return 0;
	}

}

namespace engine {
namespace profiler {

	util::Array<ProfilerManager*> g_profilerManagers; // used to find all managers across all threads
	PROPELLER_TLS ProfilerManager *g_profilerManager;

	ProfilerManager::ProfilerManager()
		: rootNode(NULL)
		, currentNode(NULL)
	{ }

	ProfilerManager::~ProfilerManager()
	{
		cleanUpChilds(rootNode);
		rootNode = NULL;
		currentNode = NULL;
	}

	Profile *ProfilerManager::getRootNode()
	{
		return rootNode;
	}

	void ProfilerManager::cleanUpChilds(Profile *node)
	{
		for (unsigned i = 0; i < node->childs.size(); ++i)
			cleanUpChilds(node->childs[i]);

		delete node;
	}

	void ProfilerManager::profileStart(const char *name)
	{
		if (currentNode == NULL)
		{
			if (rootNode == NULL)
			{
				// Root node missing!
				Profile *profile = new Profile(name, NULL);

				rootNode = profile;
				currentNode = profile;
				// Add to child of root!
				profileStart(name);
				return;
			}

			// new frame, start from root
			currentNode = rootNode;
			return;
		}
		else
		{
			// CurrentNode is something, we have a child for it!

			// try to find child from the list
			for (unsigned i = 0; i < currentNode->childs.size(); ++i)
			{
				if (currentNode->childs[i]->name == name)
				{
					// Found the child the profiler is using!

					// Switch current node to that
					currentNode = currentNode->childs[i];

					return;
				}
			}

			// Did NOT find the profiler node! Lets add one
			Profile *profile = new Profile(name, currentNode);

			currentNode->childs.push_back(profile);
			currentNode = profile; //and then set the new node as current.
		}
	}

	void ProfilerManager::profileEnd(long time)
	{
		assert(currentNode != NULL);

		// local
		++currentNode->calls;
		currentNode->totalTime += time;
		currentNode->lastTime = time;

		//global
		++rootNode->calls;
		rootNode->totalTime += time;

		currentNode = currentNode->parentNode;
	}

	void ProfilerManager::generateReport(std::vector<String> &lines)
	{
		lines.push_back("# PropellerProfiler");
		std::stringstream sstream;

		sstream << "TotalCalls: " << rootNode->calls;
		lines.push_back(sstream.str());
		sstream.str(String());

		sstream << "TotalTime: " << rootNode->totalTime << " ms";
		lines.push_back(sstream.str());
		sstream.str(String());

		lines.push_back("");

		addChildsToReport(lines, rootNode, 0);
	}

	void ProfilerManager::addChildsToReport(std::vector<String> &lines, Profile *node, unsigned depth)
	{
		String base;
		for (unsigned i = 0; i < depth; ++i)
			base.append("   ");

		std::stringstream sstream;

		sstream << base << "> Name: " << node->name;
		lines.push_back(sstream.str());
		sstream.str(String());

		sstream << base << "    TotalCalls: " << node->calls;
		lines.push_back(sstream.str());
		sstream.str(String());

		sstream << base << "    TotalTime: " << node->totalTime << " ms";
		lines.push_back(sstream.str());
		sstream.str(String());

		sstream << base << "    Average: " << node->totalTime / node->calls << " ms";
		lines.push_back(sstream.str());
		sstream.str(String());

		if (node->parentNode != NULL)
		{
			sstream << base << "    % of parent time : " << (node->totalTime / node->parentNode->totalTime) * 100.f << " %";
			lines.push_back(sstream.str());
			sstream.str(String());
		}

		for (unsigned i = 0; i < node->childs.size(); ++i)
			addChildsToReport(lines, node->childs[i], depth + 1);
	}

	void ProfilerManager::outputToStdio()
	{
		std::vector<String> lines;

		generateReport(lines);

		for (unsigned i = 0; i < lines.size(); ++i)
			std::cout << lines[i] << "\n";
	}

	void ProfilerManager::outputToLog()
	{
		std::vector<String> lines;

		generateReport(lines);

		for (unsigned i = 0; i < lines.size(); ++i)
			LOG_INFO(lines[i]);
	}

	void ProfilerManager::dumpProfilerAsJSON()
	{
		Json::Value root;

		root["timestamp"] = "time and date";

		// Fill the data into profilerData ( Find managers for all threads )
		for (unsigned i = 0; i < g_profilerManagers.getSize(); ++i)
		{
			Json::Value profilerData;
			addChildsToJSON(g_profilerManagers[i]->getRootNode(), profilerData);
			root["root"].append(profilerData);
		}


		FILE *file;

		String filename = "profiler_" + engine::sys::getCurrentTimestampForFile() + ".ProfiledPropeller";
		engine::sys::fileOpen(&file, filename, "w");
			//FILE *file = fopen(filename.c_str(), "w");

		if (file == NULL)
		{
			LOG_ERROR("Failed to save profiler JSON dump (" << filename << ")");
			return;
		}

		Json::StyledWriter writer;

		fputs(writer.write(root).c_str(), file);

		engine::sys::fileClose(file);
	}

	void ProfilerManager::addChildsToJSON(Profile *node, Json::Value &value)
	{
		// Add itself
		value["name"] = Json::Value(node->name);
		value["callcount"] = Json::Value(Json::Int64(node->calls));
		value["totaltime"] = Json::Value(Json::Int64(node->totalTime));

		Json::Value childs;

		// Add all childs
		for (unsigned i = 0; i < node->childs.size(); ++i)
		{
			Json::Value child;

			addChildsToJSON(node->childs[i], child);

			childs.append(child);
		}

		value["childs"] = childs;
	}

}
}
