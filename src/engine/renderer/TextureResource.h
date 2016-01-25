// copyright (c) lauri mäkinen 2014 - 2015
// all rights reserved.
#ifndef ENGINE_RENDERER_TEXTURERESOURCE_H
#define ENGINE_RENDERER_TEXTURERESOURCE_H

#include "engine/resource/Resource.h"
#include "engine/renderer/Texture.h"

#ifdef GLES2
#include <GLES2/gl2.h>
#endif

namespace engine {
namespace renderer {

	class TextureResource : public resource::Resource
	{
	private:
		size_t gRamSize;

		Texture *texture;

	public:
		TextureResource(Texture *texture)
			: texture(texture)
		{ }

		size_t getSize();
		size_t getGRamSize();

		const unsigned getWidth() const { return texture->width; }
		const unsigned getHeight() const { return texture->width; }

		bool hasGPUResource();

		Texture *getTexture() { return texture; }
	};

}
}

#endif
