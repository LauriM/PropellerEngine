// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_MODELRESOURCE_H
#define ENGINE_RENDERER_MODELRESOURCE_H

#include "engine/resource/Resource.h"
#include "engine/renderer/Buffer.h"
#include "engine/lang/ScopedPtr.h"

namespace engine {
namespace renderer {

	class ModelResource : public resource::Resource
	{
	private:
	public:
		unsigned strideSize;
		unsigned indicesCount;

		lang::ScopedPtr<Buffer> vertexBuffer;
		lang::ScopedPtr<Buffer> indexBuffer;

		size_t getSize();
		size_t getGRamSize();
	};

}
}

#endif
