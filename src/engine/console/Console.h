// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_CONSOLE_CONSOLESYSTEM_H
#define ENGINE_CONSOLE_CONSOLESYSTEM_H

#include "engine/util/HashMap.h"

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace engine {
namespace console {

	class CVarBase;
	class Command;

	/**
	 * Console system keeps the CVars in memory and handles loading/saving of config files.
	 *
	 * Also keeps list of the recent message history in the memory.
	 *
	 * In future this could be expanded to support small command system
	 */
	class Console {
	private:
		engine::GameInstance *instance;

	public:
		Console(engine::GameInstance *instance)
			: instance(instance)
		{ }

		typedef util::HashMap<CVarBase*> CVarList;
		typedef util::HashMap<Command*> CommandList;
		typedef util::Array<String> HistoryList;

		inline static CommandList &getCommandList()
		{
			static CommandList staticCommandList;
			return staticCommandList;
		}

		inline static CVarList &getCVarList()
		{
			static CVarList staticCVarMap;
			return staticCVarMap;
		}

		inline static HistoryList &getHistoryList() 
		{
			static HistoryList staticHistoryList;
			return staticHistoryList;
		}

		bool saveConfig(String filename);

		int execute(String cmd);
	};

}
}

#endif
