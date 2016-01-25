// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

#if defined (GL2)

namespace engine {
namespace renderer {

	struct DeviceData
	{
#ifndef OS_ANDROID
		HDC device;
		HGLRC context;
#else
		EGLSurface surface;
		EGLContext context;
		EGLDisplay display;
#endif
	};

}
}

#endif
