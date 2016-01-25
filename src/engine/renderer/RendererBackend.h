// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_RENDERERBACK_H
#define ENGINE_RENDERER_RENDERERBACK_H

#include "engine/preprocessor/platform.h"

#ifdef OS_WINDOWS

	#ifndef DEDICATED_SERVER


	#endif

	#ifdef D3D11
			#define RENDERING_ENABLED 1 

			#define RENDERER_OK
	#endif

	#ifdef GL2
		#define RENDERING_ENABLED 1

		#define RENDERER_OK
	#endif

	#ifndef RENDERER_OK
		#define NULLRENDERER
	#endif

#endif

#endif