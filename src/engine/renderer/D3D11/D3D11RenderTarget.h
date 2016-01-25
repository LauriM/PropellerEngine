// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_D3D11RENDERTARGET_H
#define ENGINE_RENDERER_D3D11RENDERTARGET_H

#include "engine/renderer/RendererBackend.h"

#if defined(D3D11)

#include "engine/renderer/RenderTarget.h"
#include <d3d11.h>

namespace engine {
namespace renderer {

	struct D3D11RenderTarget
	{
		RenderTarget header;

		ID3D11RenderTargetView *renderTargetView;
		ID3D11Texture2D *renderTargetTexture;
		ID3D11ShaderResourceView *shaderResourceView;
	};

}
}

#endif

#endif