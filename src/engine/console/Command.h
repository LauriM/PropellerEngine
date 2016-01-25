// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_CONSOLE_COMMAND_H
#define ENGINE_CONSOLE_COMMAND_H

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace engine {
namespace console {

		//Usage
		//
		//CREATE_COMMAND(Name, description)
		//{
		//	BODY;
		//}
		//
		// You can use args inside the body to read input. args is a std::vector<String>

#define CREATE_COMMAND(p_name, p_desc) \
	inline int _command_func##p_name(engine::GameInstance *instance, std::vector<String> *args);\
		class _command_class##p_name : public engine::console::Command\
				{\
		public:\
		_command_class##p_name()\
				{\
			engine::console::Console::getCommandList().insert(TO_STRING(p_name), this);\
			name = TO_STRING(p_name);\
			description = TO_STRING(p_desc);\
		}\
		int call(engine::GameInstance *instance, std::vector<String> *args) { return _command_func##p_name(instance, args); }\
		\
	};\
	_command_class##p_name p_name;\
	inline int _command_func##p_name(engine::GameInstance *instance, std::vector<String> *args)

	class Command
	{
	protected:
		String name;
		String description;

	public:
		virtual const String &getName()
		{
			return name;
		}

		const String &getDescription()
		{
			return description;
		}

		virtual int call(engine::GameInstance *gameInstance, std::vector<String> *args) = 0;

		inline int operator () (engine::GameInstance *gameInstance, std::vector<String> *args) { return call(gameInstance, args); };
	};

}
}

#endif