// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RTTI_OBJECTFACTORY_H
#define ENGINE_RTTI_OBJECTFACTORY_H

PROPELLER_FORWARD_DECLARE_2(engine, stream, Serializable);
PROPELLER_FORWARD_DECLARE_2(engine, rtti, Object);
PROPELLER_FORWARD_DECLARE_2(engine, rtti, Class);

// forward declare
namespace engine {
	struct ContextData; //TODO: forward declare structs
}

namespace engine {
namespace rtti {

	class RTTI
	{
	public:
		static Object *generateObject(const String &className, ContextData *context);
		static stream::Serializable *generateSerializable(const String &className, ContextData *context);
		static Class *getTypeInfo(const String &className);

		static void getDerivedForTypeName(const String &className, std::vector<Class*> *output);
		static void getDerivedForClass(const Class *cls, std::vector<Class*> *output);

		static bool isDerivedFrom(const Class *source, const Class *base);
	};

}
}

#endif
