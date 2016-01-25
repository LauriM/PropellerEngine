// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "RTTI.h"

#include "engine/rtti/Object.h"
#include "engine/rtti/Class.h"

namespace engine {
namespace rtti {

	//TODO: This should not be used like this.
	Object *RTTI::generateObject(const String &className, ContextData *context)
	{
		return getClassSet()[className]->generate(context);
	}

	//TODO: This should not be used like this.
	stream::Serializable *RTTI::generateSerializable(const String &className, ContextData *context)
	{
		return (stream::Serializable*)generateObject(className, context);
	}

	Class *RTTI::getTypeInfo(const String &className)
	{
		return getClassSet()[className];
	}

	void RTTI::getDerivedForTypeName(const String &className, std::vector<Class*> *output)
	{
		Class *cs = RTTI::getTypeInfo(className);

		getDerivedForClass(cs, output);
	}

	void RTTI::getDerivedForClass(const Class *cls, std::vector<Class*> *output)
	{
		ClassSet cs = getClassSet();
		ClassSet::iterator it = cs.begin();

		//Loop trough and find stuff that has className's type as parent.
		//TODO: check multiple levels of derivation!

		while (it != cs.end())
		{
			if (it->second->getBaseClass() == cls)
			{
				output->push_back(it->second);
			}

			++it;
		}
	}

	bool RTTI::isDerivedFrom(const Class *source, const Class *base)
	{
		const Class *parentClass = source->getBaseClass();

		while (parentClass != NULL)
		{
			// Is it the base?
			if (parentClass == base)
				return true;

			//Check child of it
			return isDerivedFrom(parentClass, base);
		}

		return false;
	}

}
}
