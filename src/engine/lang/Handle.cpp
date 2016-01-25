// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/lang/Handle.h"

namespace engine {
namespace lang {

	void Handle::operator = (unsigned i)
	{
		ptr = manager->getHandle(i);
		id = i;

		#ifdef _DEBUG
		if (ptr == NULL)
			LOG_ERROR("Invalid assigment for a Handle!");
		#endif
	}

	void Handle::operator = (void *p)
	{
		id = manager->createHandle(p);
		ptr = p;

#ifdef _DEBUG
		if (id == INVALID_HANDLE_ID)
			LOG_ERROR("Invalid assigment for a Handle!");
#endif
	}

	void Handle::refreshHandle()
	{
		ptr = manager->getHandle(id);
	}

	void Handle::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		strm.write(id);
	}

	void Handle::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		strm.read(id);
		ptr = manager->getHandle(id);
	}

}
}