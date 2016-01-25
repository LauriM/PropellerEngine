// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/console/Console.h"

#include "engine/console/Cvar.h"
#include "engine/console/Command.h"
#include "engine/util/StringUtil.h"
#include "engine/GameInstance.h"

namespace command {
	CREATE_COMMAND(version, "Display engine version")
	{
		LOG_INFO("Version: " TO_STRING(ENGINE_VERSION_MAJOR) "." TO_STRING(ENGINE_VERSION_MINOR));
		return 0;
	}

	CREATE_COMMAND(set, "set <cvar> <value>")
	{
		if (args->size() == 1)
		{
			LOG_INFO("Usage: set <cvar> <value>");
			return 0;
		}

		//Find the iterator based on args.
		engine::console::CVarBase *cvar;
		bool found = engine::console::Console::getCVarList().find(args->at(1), cvar);

		if (!found)
		{
			LOG_WARNING("[set] Incorrect variable name");
			return -1;
		}

		if (args->size() == 2)
		{
			// Print the cvar to log, etc
			LOG_INFO("[set] " << args->at(1) << " = " << cvar->get());
			return 0;
		}

		if(args->size() == 3)
		{
			//Set the cvar
			cvar->set(args->at(2));
			LOG_INFO("[set] " << args->at(1) << " = " << cvar->get());
			return 0;
		}

		LOG_WARNING("[set] Invalid param count");
		return -1;
	}

	CREATE_COMMAND(toggle, "toggle <cvar> <val1> <val2>")
	{

		if (args->size() == 1)
		{
			LOG_INFO("Usage: toggle <cvar> <val1> <val2>");
			return 0;
		}

		if (args->size() != 4)
		{
			LOG_WARNING("Invalid parameter count!");
			return -1;
		}

		engine::console::CVarBase *cvar;
		bool found = engine::console::Console::getCVarList().find(args->at(1), cvar);

		if (!found)
		{
			LOG_WARNING("[Toggle] can't find cvar!");
			return -1;
		}

		String val1 = args->at(2);
		String val2 = args->at(3);

		if (cvar->get() == val1)
		{
			cvar->set(val2);
			LOG_INFO("[toggle] " << args->at(1) << " = " << cvar->get());
			return 0;
		}

		if (cvar->get() == val2)
		{
			cvar->set(val1);
			LOG_INFO("[toggle] " << args->at(1) << " = " << cvar->get());
			return 0;
		}

		return 0;
	}

	CREATE_COMMAND(listcommands, "List all console commands.")
	{
		engine::console::Console::CommandList &commandList = engine::console::Console::getCommandList();

		LOG_INFO("Commands:");

		engine::console::Console::CommandList::Iterator it = commandList.begin();

		unsigned count = 0;
		unsigned indent = 20;

		while (!it.isAtEnd())
		{
			unsigned nameLen = it.getValue()->getName().length();
			unsigned padding = indent - nameLen;

			String pad = " ";

			for (unsigned i = 0; i < padding; ++i)
				pad += " ";

			LOG_INFO("* " << it.getValue()->getName() << pad << " : " << it.getValue()->getDescription());
			++it;
			++count;
		}

		LOG_INFO("Commands: " << count);

		return 0;
	}

	CREATE_COMMAND(listcvars, "List all cvars")
	{
		engine::console::Console::CVarList &cvarList = engine::console::Console::getCVarList();

		LOG_INFO("CVars:");

		engine::console::Console::CVarList::Iterator it = cvarList.begin();

		unsigned count = 0;

		while (!it.isAtEnd())
		{
			LOG_INFO("* " << it.getKey());
			++it;
			++count;
		}

		LOG_INFO("CVars: " << count);

		return 0;
	}

	CREATE_COMMAND(exec, "Execute configuration file.")
	{
		if (args->size() < 2)
		{
			LOG_ERROR("[exec] incorrect variable count!");
			return -1;
		}

		std::ifstream file;
		file.open(args->at(1).c_str());

		if (!file.is_open()){
			LOG_ERROR("[exec] Can't open file " << args->at(1));
			return false;
		}

		String line;

		while (std::getline(file, line))
		{
			instance->getConsole()->execute(line);
		}

		file.close();

		LOG_INFO("[exec] file " << args->at(1) << " loaded");

		return 0;
	}

	CREATE_COMMAND(echo, "echo text to console/log")
	{
		// just echo all stuff in the string expect 'echo '
		String message = " ";

		for (unsigned i = 1; i < args->size(); ++i)
		{
			message.append(args->at(i) + " ");
		}

		DEBUG_PRINT(message);
		LOG_INFO(message);

		return 0;
	}
}


namespace engine {
namespace console {

	/**
	 * Saves current configs to disk with a specific filename.
	 *
	 * The file is created if it doesn't exists.
	 *
	 * @return bool was the operation succesful
	 */
	bool Console::saveConfig(String filename)
	{
		std::ofstream file( filename.c_str() );

		Console::CVarList::Iterator it = getCVarList().begin();

		while (!it.isAtEnd()){
			if(it.getValue()->isSaved())
			{
				String output = "set ";

				output += it.getValue()->getName();
				output += " ";
				output += it.getValue()->get();

				file << output << "\n";
			}
			++it;
		}

		file.close();

		LOG_INFO("Configs written to disk");
		return true;
	}

	//Finds the command, parses arguments out, and gives it to the command.
	int Console::execute(String command)
	{
		if (command == "")
			return 0;

		if (command.substr(0, 1) == "#")
			return 0;

		//Get args
		std::vector<String> args;
		engine::util::explode(&args, command, ' ');

		Command *cmd;
		if(!Console::getCommandList().find(args[0], cmd))
		{
			LOG_WARNING("[Console] Invalid command name! (" << command << ")");
			return -1; //Could not find it!
		}
		
		//run it
		return cmd->call(instance, &args);
	}
}
}
