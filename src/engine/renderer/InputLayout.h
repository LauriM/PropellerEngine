// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_INPUTLAYOUT_H
#define ENGINE_RENDERER_INPUTLAYOUT_H

#include "engine/renderer/RendererEnums.h"

namespace engine {
namespace renderer {

	struct InputElement
	{
		Semantic semantic;
		InputFormat inputFormat;
	};

	struct InputLayout
	{
		// Basic information about the layout created is shared between API's
		unsigned inputElementCount;
		InputElement *inputElements;
		size_t stride;
	};

	// Used to create the InputLayout
	struct InputLayoutDesc
	{
		unsigned inputElementCount;
		InputElement inputElements[MAX_INPUTLAYOUT_SIZE];
	};

}
}

#endif