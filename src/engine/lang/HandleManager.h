// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_LANG_HANDLEMANAGER_H
#define ENGINE_LANG_HANDLEMANAGER_H

PROPELLER_FORWARD_DECLARE_2(engine, stream, Serializable);

#define INVALID_HANDLE_ID 0

namespace engine {
namespace lang {

	union HandleSlot
	{
		unsigned nextIndex;
		void *ptr;
	};

	class HandleManager
	{
	private:
		HandleSlot *handles;

		unsigned handleCount;
		unsigned handleCapacity;
		unsigned nextSlot;
		unsigned rmCount;

		void resize(unsigned size);

	public:
		HandleManager()
			: handleCount(0)
			, handleCapacity(1)
			, nextSlot(0)
			, rmCount(0)
		{
			handles = (HandleSlot*)malloc(sizeof(HandleSlot) * handleCapacity);
		}

		~HandleManager()
		{
			free(handles);
		}

		unsigned createHandle(void *ptr);
		void releaseHandle(unsigned id);
		stream::Serializable *getHandle(unsigned int id) const;

		void releaseAllHandles();

		unsigned getHandleCount() { return handleCount; }
	};

}
}

#endif