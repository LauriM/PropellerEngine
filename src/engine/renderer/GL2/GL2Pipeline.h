// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

#include "engine/renderer/Pipeline.h"

#if defined (GL2)

namespace engine {
namespace renderer {

	struct GL2Pipeline
	{
		Pipeline header;

		GLuint program;
	};

}
}

#endif
