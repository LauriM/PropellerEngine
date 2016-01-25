// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_CONSOLE_CVAR_H
#define ENGINE_CONSOLE_CVAR_H

#include "boost/lexical_cast.hpp"

#include "engine/console/Console.h"

namespace engine {
namespace console {

#define CVAR(p_type, p_name, p_def_value, p_saved) \
		engine::console::CVar<p_type> p_name ( TO_STRING(p_name), p_def_value, p_saved)

#define EXTERN_CVAR(p_type,p_name) \
		extern engine::console::CVar<p_type> p_name

	class CVarBase
	{
	public:
		CVarBase()
		{}

		virtual ~CVarBase() {};

		virtual bool set(String value) = 0;
		virtual String get() const = 0;

		virtual const String& getName() = 0;

		virtual bool isSaved() = 0;
	};

	template <typename T>
	class CVar : public CVarBase
	{
	protected:
		String name;
		T data;
		bool saved;

	public:
		CVar(String name,T data,bool saved)
			: CVarBase()
			  , name(name)
			  , data(data)
			  , saved(saved)
			{
				Console::getCVarList().insert(name.c_str(), this);
			}

		virtual bool set(String value)
		{
			data = boost::lexical_cast<T,String>(value);
			return false;
		}

		virtual String get() const
		{
			return boost::lexical_cast<String,T>(data);
		}

		virtual const String& getName()
		{
			return name;
		}

		inline T& operator * ()
		{
			return data;
		}

		bool isSaved()
		{
			return saved;
		}
	};

}
}

#endif
