// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/rtti/Object.h"
#include "engine/rtti/Class.h"

#include "engine/memory/BlockPoolAllocator.h"

namespace engine {
namespace rtti {

	static Class objectTypeInfo("Object", NULL, sizeof(Object));

	engine::rtti::Class *Object::getStaticTypeInfo()
	{
		return &objectTypeInfo;
	}

	Class *Object::getTypeInfo()
	{
		return &objectTypeInfo;
	}

	void* Object::operator new(size_t size)
	{
		return engine::lang::g_blockPoolAllocator.allocate(size);
	}

	void Object::operator delete(void *ptr)
	{
		engine::lang::g_blockPoolAllocator.free(ptr);
	}

}
}
