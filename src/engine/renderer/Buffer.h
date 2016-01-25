// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_BUFFER_H
#define ENGINE_RENDERER_BUFFER_H

#include "engine/renderer/RendererEnums.h"

namespace engine {
namespace renderer {

	struct Buffer
	{
		BufferType type;
		BufferUsage usage;
		size_t size;
	};

}
}

#endif
