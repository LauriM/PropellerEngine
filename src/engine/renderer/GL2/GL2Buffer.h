// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

#include "engine/renderer/Buffer.h"

#if defined(GL2)

namespace engine {
namespace renderer {

	struct GL2Buffer
	{
		Buffer header;

		GLuint buffer;
	};

}
}

#endif