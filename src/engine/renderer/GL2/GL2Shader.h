// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_D3D11SHADER_H
#define ENGINE_RENDERER_D3D11SHADER_H

#include "engine/renderer/RendererBackend.h"

#if defined(GL2)

#include "engine/renderer/Shader.h"

namespace engine {
namespace renderer {

	struct GL2Shader
	{
		Shader header;

		GLuint shaderId;
	};

}
}

#endif

#endif