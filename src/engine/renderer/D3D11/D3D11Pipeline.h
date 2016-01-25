// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

#include "engine/renderer/Pipeline.h"

#if defined (D3D11)

namespace engine {
namespace renderer {

	struct D3D11Pipeline
	{
		Pipeline header;

		ID3D11RasterizerState *rasterState;
		ID3D11SamplerState *samplerState;
		ID3D11BlendState *blendState;
		ID3D11DepthStencilState *depthState;
	};

}
}

#endif
