// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/TextureResource.h"

namespace engine {
namespace renderer {

	size_t TextureResource::getSize()
	{
		return sizeof(TextureResource) + sizeof(Texture);
	}

	size_t TextureResource::getGRamSize()
	{
		LOG_WARNING("GetGRAMSize() for texture is not implemented.");
		return 0;
	}

	bool TextureResource::hasGPUResource() { return true; }

}
}
