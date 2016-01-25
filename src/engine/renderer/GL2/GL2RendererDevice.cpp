// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/RendererDevice.h"

#if defined(GL2)

#ifdef OS_ANDROID
#include <android_native_app_glue.h>
#endif

#ifndef OS_ANDROID
#include <GL/glew.h>
#include <GL/GL.h>
#else
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES2/gl2ext.h>
#endif

#include "engine/console/Cvar.h"
#include "engine/renderer/RendererEnums.h"
#include "engine/renderer/Pipeline.h"
#include "engine/renderer/StateDescriptor.h"
#include "engine/renderer/ShaderResource.h"
#include "engine/renderer/TextureResource.h"
#include "engine/renderer/InputLayout.h"
#include "engine/renderer/GL2/GL2DeviceData.h"
#include "engine/renderer/GL2/GL2InputLayout.h"
#include "engine/renderer/GL2/GL2Pipeline.h"
#include "engine/renderer/GL2/GL2Helper.h"
#include "engine/renderer/GL2/GL2Shader.h"
#include "engine/renderer/GL2/GL2Buffer.h"
#include "engine/renderer/Viewport.h"
#include "engine/renderer/RendererEnums.h"
#include "engine/renderer/GL2/GL2Texture.h"
#include "engine/renderer/DrawDescriptor.h"

namespace cvar {
	EXTERN_CVAR(int, r_width);
	EXTERN_CVAR(int, r_height);
	EXTERN_CVAR(int, r_vsync);
}

namespace engine {
namespace renderer {

	RendererDevice *createRendererDevice(void *hwnd)
	{
		RendererDevice *device = new RendererDevice();

		device->setHwnd(hwnd);

		return device;
	}

	RendererDevice::RendererDevice()
	{
		deviceData = (DeviceData*)malloc(sizeof(DeviceData));
		
		// Actual GL init happens in init(), after hwnd is set
	}

	RendererDevice::~RendererDevice()
	{
		free(deviceData);
	}

	bool RendererDevice::init()
	{
		PROFILE;

#ifndef OS_ANDROID // Android uses EGL and not glew
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
			PFD_TYPE_RGBA,
			24,
			24
		};

		deviceData->device = GetDC((HWND)hwnd);
		int pixelFormat = ChoosePixelFormat(deviceData->device, &pfd);
		SetPixelFormat(deviceData->device, pixelFormat, &pfd);
		deviceData->context = wglCreateContext(deviceData->device);

		wglMakeCurrent(deviceData->device, deviceData->context);

		glewInit();
#endif

#ifdef OS_ANDROID
		const EGLint attribs[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_DEPTH_SIZE, 24,
			EGL_NONE
		};

		EGLint w, h, dummy, format;
		EGLConfig config;
		EGLint numConfigs;

		EGLint attribList[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		deviceData->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

		LOG_INFO("Display ptr: " << deviceData->display);

		EGLBoolean errorCode = eglInitialize(deviceData->display, 0, 0);
		LOG_INFO("ErrorCode eglInit: " << errorCode);
		errorCode = eglChooseConfig(deviceData->display, attribs, &config, 1, &numConfigs);
		LOG_INFO("ErrorCode chooseConfig: " << errorCode);
		errorCode = eglGetConfigAttrib(deviceData->display, config, EGL_NATIVE_VISUAL_ID, &format);
		LOG_INFO("ErrorCode getConfigAttrib: " << errorCode);
		LOG_INFO("format: " << format);

		ANativeWindow_setBuffersGeometry((ANativeWindow*)hwnd, 0, 0, format);

		EGLint *hack = NULL;
		deviceData->surface = eglCreateWindowSurface(deviceData->display, config, (ANativeWindow*)hwnd, hack);
		LOG_INFO("Surface pointer: " << (void*)deviceData->surface);

		deviceData->context = eglCreateContext(deviceData->display, config, NULL, attribList);

		//LOG_INFO("window ptr: " << (void*)window);
		LOG_INFO("context ptr: " << (void*)deviceData->context);

		if (eglMakeCurrent(deviceData->display, deviceData->surface, deviceData->surface, deviceData->context) == EGL_FALSE) {
			LOG_ERROR("Unable to eglMakeCurrent");
			return false;
		}

		eglQuerySurface(deviceData->display, deviceData->surface, EGL_WIDTH, &w);
		eglQuerySurface(deviceData->display, deviceData->surface, EGL_HEIGHT, &h);

		*cvar::r_width = w;
		*cvar::r_height = h;

		GLERRORCHECK;
#endif

		glEnable(GL_TEXTURE_2D);
		//glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		//glDepthFunc(GL_LESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
		//glBlendFunc(GL_ONE, GL_ONE);

		return true;
	}

	void RendererDevice::uninit()
	{
	}

	// Stub, GL2 has the shader creation logic inside the ShaderLoader class
	Shader *RendererDevice::createShader(ShaderType type, const void *buffer, size_t bufferSize) { return NULL; }

	void RendererDevice::beginFrame()
	{
	}

	void RendererDevice::endFrame()
	{
#ifndef OS_ANDROID
		SwapBuffers(deviceData->device);
#else
		eglSwapBuffers(deviceData->display, deviceData->surface);
#endif
	}

	Pipeline *RendererDevice::createRasterizerPipeline(const StateDescriptor *stateDescriptor, InputLayout *inputLayout, Shader *vertexShader, Shader *pixelShader)
	{
		// GL needs to link the shaders here and keep the program around
		// Statedescriptor, etc do not need anything to be done here, just keep the data around

		GL2Pipeline *pipeline = new GL2Pipeline();

		pipeline->header.state = *stateDescriptor;
		pipeline->header.pixelShader = pixelShader;
		pipeline->header.vertexShader = vertexShader;
		pipeline->header.inputLayout = inputLayout;

		// link the programs

		pipeline->program = glCreateProgram();
		GLERRORCHECK;

		glAttachShader(pipeline->program, ((GL2Shader*)vertexShader)->shaderId);
		glAttachShader(pipeline->program, ((GL2Shader*)pixelShader)->shaderId);
		glLinkProgram(pipeline->program);
		GLERRORCHECK;

		GLint compileResult;
		glGetProgramiv(pipeline->program, GL_LINK_STATUS, &compileResult);
		if (compileResult != GL_TRUE)
		{
			LOG_ERROR(" >>> Unable to link program! <<<");

			GLint result;
			int logLength;
			bool error = false;

			glGetProgramiv(pipeline->program, GL_LINK_STATUS, &result);
			glGetProgramiv(pipeline->program, GL_INFO_LOG_LENGTH, &logLength);
			char errorMsg[1200] = "\n";
			glGetProgramInfoLog(pipeline->program, logLength, NULL, errorMsg);

			LOG_ERROR(errorMsg);

			return NULL;
		}

		LOG_INFO("[RendererDevice] .GLSL link ok !");

		return &pipeline->header;
	}

	RenderTarget *RendererDevice::createBackbufferRenderTarget()
	{
		return NULL;
	}

	RenderTarget *RendererDevice::createRenderTarget(unsigned width, unsigned height)
	{
		return NULL;
	}

	Buffer *RendererDevice::createBuffer(BufferType bufferType, size_t size, BufferUsage usage)
	{
		PROFILE;

		GLuint bufferId;

		glGenBuffers(1, &bufferId);
		GLERRORCHECK;

		if (bufferId == 0)
		{
			LOG_ERROR("[RendererDevice] Failed to allocate buffer on GPU!");
			return NULL;
		}

		GL2Buffer *b = new GL2Buffer();

		b->buffer = bufferId;
		b->header.size = size;
		b->header.type = bufferType;
		b->header.usage = usage;

		return &b->header;
	}

	// Mapping not needed in gl!
	void RendererDevice::mapBuffer(Buffer *buffer) { } 

	// Mapping not needed in gl!
	void RendererDevice::unmapBuffer(Buffer *buffer) { }

	void RendererDevice::copyData(Buffer *buffer, void *data, size_t size)
	{
		PROFILE;

		assert(size <= buffer->size);

		switch (buffer->type)
		{
		case BUFFERTYPE_VERTEX:
			glBindBuffer(GL_ARRAY_BUFFER, ((GL2Buffer*)buffer)->buffer);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			GLERRORCHECK;
			glBindBuffer(GL_ARRAY_BUFFER, 0u);
			break;
		case BUFFERTYPE_INDEX:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((GL2Buffer*)buffer)->buffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			GLERRORCHECK;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			break;
		case BUFFERTYPE_CONSTANT:
			//TODO: constant buffer not working
			break;
		}
	}

	void RendererDevice::copyData(Buffer *buffer, size_t offset, void *data, size_t size)
	{
		PROFILE;

		assert(size <= buffer->size);

		switch (buffer->type)
		{
		case BUFFERTYPE_VERTEX:
			glBindBuffer(GL_ARRAY_BUFFER, ((GL2Buffer*)buffer)->buffer);
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
			GLERRORCHECK;
			glBindBuffer(GL_ARRAY_BUFFER, 0u);
			break;
		case BUFFERTYPE_INDEX:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((GL2Buffer*)buffer)->buffer);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
			GLERRORCHECK;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
			break;
		case BUFFERTYPE_CONSTANT:
			LOG_INFO("Hahaa! Ain't gonna work!");
			break;
		}
	}

	InputLayout *RendererDevice::createInputLayout(const InputLayoutDesc &desc, ShaderResource *vertexResource)
	{
		// Input layout is not thing in OpenGL, going to simulate it.
		// Shader resource is going to be ignored by OpenGL.

		GL2InputLayout *inputLayout = new GL2InputLayout();

		inputLayout->header.inputElementCount = desc.inputElementCount;
		inputLayout->header.inputElements = (InputElement*)malloc(sizeof(InputElement) * desc.inputElementCount);

		// copy data over
		unsigned stride = 0;
		for (unsigned i = 0; i < desc.inputElementCount; ++i)
		{
			inputLayout->header.inputElements[i] = desc.inputElements[i];

			switch (desc.inputElements[i].inputFormat)
			{
			case INPUTFORMAT_FLOAT_X:
				stride += 1;
				break;
			case INPUTFORMAT_FLOAT_XY:
				stride += 2;
				break;
			case INPUTFORMAT_FLOAT_XYZ:
				stride += 3;
				break;
			case INPUTFORMAT_FLOAT_XYZW:
				stride += 4;
				break;
			default:
				break;
			}
		}

		inputLayout->header.stride = stride;

		return &inputLayout->header;
	}

	Texture *RendererDevice::createCubemapTextureFromTextures(TextureResource *textureResources[6])
	{
		return NULL;
	}

	void RendererDevice::setPipeline(Pipeline *pipeline)
	{
		GL2Pipeline *glPipeline = (GL2Pipeline*)pipeline;

		// ! Set the program
		glUseProgram(glPipeline->program);

		// ! Setup the inputlayout
		size_t offset = 0;

		unsigned size = 0;
		GLint attribLocation = 0;

		char *semanticNames[] = {
			"dcl_Input0",
			"dcl_Input1",
			"dcl_Input2",
			"dcl_Input3",
			"dcl_Input4",
			"dcl_Input5",
			"dcl_Input6",
		};

		//dcl_Input0
		unsigned inputPos = 0;

		for (unsigned i = 0; i < pipeline->inputLayout->inputElementCount; ++i)
		{
			InputFormat &f = pipeline->inputLayout->inputElements[i].inputFormat;
			Semantic &s = pipeline->inputLayout->inputElements[i].semantic;

			switch (f)
			{
			case INPUTFORMAT_FLOAT_X:
				size = 1;
				break;
			case INPUTFORMAT_FLOAT_XY:
				size = 2;
				break;
			case INPUTFORMAT_FLOAT_XYZ:
				size = 3;
				break;
			case INPUTFORMAT_FLOAT_XYZW:
				size = 4;
				break;
			}

			attribLocation = glGetAttribLocation(glPipeline->program, semanticNames[inputPos]);
			GLERRORCHECK;

			glEnableVertexAttribArray(attribLocation);
			GLERRORCHECK;

			glVertexAttribPointer(attribLocation, size, GL_FLOAT, GL_FALSE, pipeline->inputLayout->stride * sizeof(float), (void*)(offset * 4));
			GLERRORCHECK;

			offset += size;
			++inputPos;
		}

		//Note for the person reading this:
		// The GL2 port was done in kinda of a hurry, making it maybe not the best one.
		// For example the blend state is just hacked there to make it work.

		//TODO: Samplers
		//TODO: depth clip

		switch (pipeline->state.blendMode)
		{
		case BLEND_ADD:
		case BLEND_MAX:

			break;

		default:
		case BLEND_NONE:
			break;
		}
	}

	void RendererDevice::setPSTextureResource(unsigned slot, Texture *resource)
	{
		glActiveTexture(GL_TEXTURE0);
		GLERRORCHECK;
		glBindTexture(GL_TEXTURE_2D, ((GL2Texture*)resource)->textureId);
		GLERRORCHECK;

		/*
		GLint texLocation = glGetUniformLocation(shaderProgram->getProgramId(), "texture");
		GLERRORCHECK;
		glUniform1i(texLocation, slot);
		GLERRORCHECK;
		*/
	}

	void RendererDevice::setPSTextureResource(unsigned slot, RenderTarget *resource)
	{

	}

	void RendererDevice::setBackbuffer(RenderTarget *target)
	{

	}

	void RendererDevice::setVertexBuffer(Buffer *buffer)
	{
		glBindBuffer(GL_ARRAY_BUFFER, ((GL2Buffer*)buffer)->buffer);
		GLERRORCHECK;
	}

	void RendererDevice::setIndexBuffer(Buffer *buffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ((GL2Buffer*)buffer)->buffer);
		GLERRORCHECK;
	}

	void RendererDevice::setVSConstantBuffer(Buffer *buffer, unsigned slot)
	{

	}

	void RendererDevice::setPSConstantBuffer(Buffer *buffer, unsigned slot)
	{
	}

	void RendererDevice::draw(const DrawDescriptor &desc)
	{
		switch(desc.topology)
		{
		case PRIMITIVETOPOLOGY_TRIANGLELIST:
			glDrawElements(GL_TRIANGLES, desc.drawCount, GL_UNSIGNED_SHORT, 0);
			break;
		case PRIMITIVETOPOLOGY_LINELIST:
			LOG_WARNING("linelist not supported yet on GL2");
			break;
		}
	}

	void RendererDevice::clear(const RenderTarget *target, const math::Vec4 color)
	{
		glClearColor(color.x, color.y, color.z, color.w);
#ifdef OS_ANDROID
		glClearDepthf(1.f);
#else
		glClearDepth(1.f);
#endif
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererDevice::setViewport(Viewport *viewport)
	{
		glViewport(viewport->leftX, viewport->leftY, viewport->width, viewport->height);

		GLERRORCHECK;
	}

}
}

#endif