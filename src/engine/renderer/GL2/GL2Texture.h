// copyright (c) lauri mäkinen 2014 - 2015
// all rights reserved.
#pragma once

#include "engine/renderer/Texture.h"

#if defined (GL2)

#ifndef OS_ANDROID
#include <GL/glew.h>
#include <GL/GL.h>
#else
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

namespace engine {
namespace renderer {

	struct GL2Texture {
		Texture header;

		GLuint textureId;
	};

}
}

#endif
