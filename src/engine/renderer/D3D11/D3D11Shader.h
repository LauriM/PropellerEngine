// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_D3D11SHADER_H
#define ENGINE_RENDERER_D3D11SHADER_H

#include "engine/renderer/RendererBackend.h"

#if defined(D3D11)

#include "engine/renderer/Shader.h"

#include <d3d11.h>

namespace engine {
namespace renderer {

	struct D3D11Shader
	{
		Shader header;

		union {
			ID3D11VertexShader *vertexShader;
			ID3D11PixelShader *pixelShader;
		};
	};

}
}

#endif

#endif