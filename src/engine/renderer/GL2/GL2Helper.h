// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef RENDERER_GLES2HELPER_H
#define RENDERER_GLES2HELPER_H

#define GLERRORCHECK {\
	GLint error = glGetError();\
	if(error!=0){ LOG_ERROR("GL ERROR " << error << " func: " << __FUNCTION__ ); }\
		}

#endif