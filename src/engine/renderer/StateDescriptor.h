// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_STATEDESCRIPTOR_H
#define ENGINE_RENDERER_STATEDESCRIPTOR_H

#include "engine/renderer/RendererEnums.h"

namespace engine {
namespace renderer {

	struct StateDescriptor
	{
		BlendMode blendMode;
		SamplerState samplerState;

		FillMode fillMode;
		CullMode cullMode;
		bool depthClipEnabled;

	};

}
}

#endif