// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_D3D11INPUTLAYOUT_H
#define ENGINE_RENDERER_D3D11INPUTLAYOUT_H

#include "engine/renderer/InputLayout.h"

#if defined (D3D11)

#include <d3d11.h>

namespace engine {
namespace renderer {

	struct D3D11InputLayout
	{
		InputLayout header;

		ID3D11InputLayout *layout;
	};

}
}

#endif

#endif