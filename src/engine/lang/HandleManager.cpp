// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/lang/HandleManager.h"

namespace engine {
namespace lang {

	void HandleManager::resize(unsigned size)
	{
		handles = (HandleSlot*)realloc(handles, sizeof(HandleSlot)* size);
		handleCapacity = size;
	}

	unsigned HandleManager::createHandle(void *ptr)
	{
		if (rmCount <= 0)
		{

			if (nextSlot >= handleCapacity)
				resize(handleCapacity * 2);

			handles[nextSlot].ptr = ptr;

			++handleCount;
			++nextSlot;
			return nextSlot - 1;
		}

		//Reuse old slot
		unsigned nextIndex = handles[nextSlot].nextIndex;
		handles[nextSlot].ptr = ptr;

		unsigned handleId = nextSlot;

		nextSlot = nextIndex;

		--rmCount;
		++handleCount;

		return handleId;
	}

	void HandleManager::releaseHandle(unsigned id)
	{
		handles[id].nextIndex = nextSlot;
		nextSlot = id;

		++rmCount;
		--handleCount;
	}

	stream::Serializable *HandleManager::getHandle(unsigned id) const
	{
		return (stream::Serializable*)handles[id].ptr;
	}

	void HandleManager::releaseAllHandles()
	{
		DEBUG_PRINT(" !! RELEASING ALL HANDLES !!");
		DEBUG_PRINT("THIS IS NOT IMPLEMENTED!");
	}

}
}