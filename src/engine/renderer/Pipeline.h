// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_PIPELINE_H
#define ENGINE_RENDERER_PIPELINE_H

#include "engine/renderer/StateDescriptor.h"

namespace engine {
namespace renderer {

	struct Shader;
	struct InputLayout;

	struct Pipeline
	{
		StateDescriptor state;
		Shader *vertexShader;
		Shader *pixelShader;
		InputLayout *inputLayout;
	};

}
}

#endif