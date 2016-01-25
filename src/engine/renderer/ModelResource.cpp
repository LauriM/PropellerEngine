// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/ModelResource.h"
#include "engine/renderer/RendererBackend.h"

namespace engine {
namespace renderer {

	size_t ModelResource::getGRamSize()
	{
#if defined (RENDERING_ENABLED)
		return vertexBuffer->size + indexBuffer->size;
#else
		return 0;
#endif
	}

	size_t ModelResource::getSize()
	{
		return sizeof(ModelResource);
	}

}
}