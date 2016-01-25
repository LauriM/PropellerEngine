// copyright (c) lauri mäkinen 2014 - 2015
// all rights reserved.
#ifndef ENGINE_RENDERER_TEXTURE_H
#define ENGINE_RENDERER_TEXTURE_H

#include "engine/renderer/RendererEnums.h"

namespace engine {
namespace renderer {

	struct Texture {
		unsigned width;
		unsigned height;

		TextureType type;
	};

}
}

#endif