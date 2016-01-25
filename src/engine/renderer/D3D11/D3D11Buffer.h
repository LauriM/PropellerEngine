// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_D3D11BUFFER_H
#define ENGINE_RENDERER_D3D11BUFFER_H

#include "engine/renderer/Buffer.h"

#if defined(D3D11)

#include <d3d11.h>

PROPELLER_FORWARD_DECLARE_STRUCT_2(engine, sys, Mutex);

namespace engine {
namespace renderer {

	struct D3D11Buffer
	{
		Buffer header;

		ID3D11Buffer *buffer;
		void *mappedPointer;
		sys::Mutex *mutex;
	};

}
}

#endif

#endif