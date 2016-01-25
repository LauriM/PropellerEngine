// copyright (c) lauri mäkinen 2014 - 2015
// all rights reserved.
#ifndef ENGINE_RENDERER_D3D11TEXTURE_H
#define ENGINE_RENDERER_D3D11TEXTURE_H

#include "engine/renderer/Texture.h"

#if defined (D3D11)

#include <d3d11.h>

namespace engine {
namespace renderer {

	struct D3D11Texture {
		Texture header;

		ID3D11Resource *resource;
		ID3D11ShaderResourceView *shaderResource;
	};

}
}

#endif

#endif
