// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_LANG_HANDLE_H
#define ENGINE_LANG_HANDLE_H

#include "engine/lang/HandleManager.h"

#include "engine/stream/OutputStream.h"
#include "engine/stream/InputStream.h"

namespace engine {
namespace lang {

	//Just a "pointer", that knows the id in the handlemanager also.

	class Handle
	{
	private:
		HandleManager *manager;

	protected:
		void *ptr;
		unsigned id;

	public:
		Handle(HandleManager *manager)
			: id(INVALID_HANDLE_ID)
			, manager(manager)
		{ }

		Handle(HandleManager *manager, unsigned id)
			: id(id)
			, manager(manager)
		{
			ptr = manager->getHandle(id);
		}

		Handle(HandleManager *manager, void *ptr)
			: ptr(ptr)
			, manager(manager)
		{
			id = manager->createHandle(ptr);
		}

		void operator = (unsigned i);
		void operator = (void *p);

		//Used in serialization
		operator unsigned () const
		{
			return id;
		}

		const void * operator -> () const
		{
			return ptr;
		}

		const bool operator == (const Handle &other) const
		{
			return id == other.id;
		}

		const bool operator != (const Handle &other) const
		{
			return id != other.id;
		}

		void operator = (const Handle &other)
		{
			ptr = other.ptr;
			id = other.id;
		}

		void * getPtr()
		{
			return ptr;
		}

		template<typename T>
		T* getPtrByType()
		{
			return (T*)ptr;
		}

		//Refresh handle is called when id's are assigned before the targets behind the pointers are created
		//May happen during loading of files
		void refreshHandle();

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);
	};

}
}

#endif
