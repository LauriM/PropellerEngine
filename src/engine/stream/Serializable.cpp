// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/stream/Serializable.h"

#include "engine/stream/OutputStream.h"
#include "engine/stream/InputStream.h"
#include "engine/lang/HandleManager.h"

namespace engine {
namespace stream {

	DECLARE_BASE_CLASS(Serializable);

	Serializable::Serializable(void *context)
		: Object(context)
		, handleid(-1)
	{
		if (isContextValid()) //If ok, the trick works!
			handleid = getHandleManager()->createHandle(this);
	}

	Serializable::~Serializable()
	{
		if (isContextValid())
			getHandleManager()->releaseHandle(handleid);
	}

}
}