// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RTTI_OBJECT_H
#define ENGINE_RTTI_OBJECT_H

#include "engine/rtti/RTTI.h"
#include "engine/Context.h"

PROPELLER_FORWARD_DECLARE_2(engine, rtti, Class);

namespace engine {
namespace rtti {

	class Object : public Context
	{
	public:
		Object(void *context)
			: Context(context)
		{ }

		void* operator new(size_t);
		void operator delete(void*);

		static engine::rtti::Class *getStaticTypeInfo();

		virtual Class *getTypeInfo() = 0;
#ifdef _EDITOR
//		virtual const String &getSourcePath() = 0;
#endif
	};

	template <typename T1, typename T2>
	T1* dynamicCast(T2 *ptr)
	{
		if (ptr == NULL)
			return NULL;

		engine::rtti::Class *target = T1::getStaticTypeInfo();
		engine::rtti::Class *src =    ptr->getTypeInfo();

		// Target and the source is the same
		if (target == src)
			return (T1*)(ptr);

		//Find if ptr has T1 in one of its baseclasses.
		if (engine::rtti::RTTI::isDerivedFrom(target, src))
			return (T1*)(ptr);

		if (engine::rtti::RTTI::isDerivedFrom(src, target))
			return (T1*)(ptr);

		// if the source is object, the cast is always correct because everything is derived from it.
		if (src == Object::getStaticTypeInfo())
			return (T1*)(ptr);

		// Cast failed, return NULL!
#ifndef _EDITOR
		return NULL;
#else
		//DEBUG_PRINT("dynamic_cast used because rcc++ RTTI merging gives invalid dynamicCasts!");
		return dynamic_cast<T1*>(ptr);
#endif
	}

	template <typename T>
	static T *generate(ContextData *context)
	{
		return engine::rtti::dynamicCast<T>(rtti::RTTI::generateSerializable(T::getStaticTypeInfo()->getTypeName(), context));
	}

}
}

#endif
