// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_D3D11DEVICEDATA_H
#define ENGINE_RENDERER_D3D11DEVICEDATA_H

#if defined (D3D11)

#include <d3d11.h>

namespace engine {
namespace renderer {

	struct DeviceData
	{
		IDXGISwapChain *swapChain;
		ID3D11Device *device;
		ID3D11DeviceContext *context;

		ID3D11Texture2D *backBufferTexture;
		ID3D11DepthStencilView *depthStencilView;
		ID3D11Texture2D *depthStencilBuffer;
		ID3D11DepthStencilState *depthStencilState;
	};

}
}

#endif

#endif