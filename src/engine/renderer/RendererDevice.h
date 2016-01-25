// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_RENDERERDEVICE_H
#define ENGINE_RENDERER_RENDERERDEVICE_H

#include "engine/math/Vector.h"
#include "engine/renderer/RendererEnums.h"

namespace engine {
namespace renderer {

	struct DeviceData;
	struct Shader;
	struct Pipeline;
	struct StateDescriptor;
	struct RenderTarget;
	struct Buffer;
	struct InputLayout;
	struct InputLayoutDesc;
	struct Texture;
	struct DrawDescriptor;
	struct Viewport;
	class ShaderResource;
	class TextureResource;

	class RendererDevice
	{
	private:
		// Opaque pointer to device specific data
		DeviceData *deviceData;
		void *hwnd;

		math::Vec2i resolution;

		// Current pipeline in use
		Pipeline *pipeline;

	public:
		RendererDevice();
		~RendererDevice();

		bool init();
		void uninit();

		void beginFrame();
		void endFrame();

		void setHwnd(void *h) { hwnd = h; }

		// InputLayouts
		InputLayout *createInputLayout(const InputLayoutDesc &inputLayoutDesc, ShaderResource *vertexResource);

		// Create a shader from memory
		Shader *createShader(ShaderType type, const void *buffer, size_t bufferSize);

		// Create backbuffer render target, texture for this is used on the flip processes
		RenderTarget *createBackbufferRenderTarget();
		RenderTarget *createRenderTarget(unsigned width, unsigned height); //TODO: Add format

		// Create Pipeline structs
		Pipeline *createRasterizerPipeline(const StateDescriptor *stateDescriptor, InputLayout *inputLayout, Shader *vertexShader, Shader *pixelShader);

		// Buffers
		Buffer *createBuffer(BufferType bufferType, size_t size, BufferUsage usage);

		// ---------
		//  "Usage" commands
		// ---------

		void setPipeline(Pipeline *pipeline);

		void setPSTextureResource(unsigned slot, Texture *resource);
		void setPSTextureResource(unsigned slot, RenderTarget *resource);

		void setBackbuffer(RenderTarget *target);

		void setVertexBuffer(Buffer *buffer);
		void setIndexBuffer(Buffer *buffer);
		void setVSConstantBuffer(Buffer *buffer, unsigned slot);
		void setPSConstantBuffer(Buffer *buffer, unsigned slot);

		void draw(const DrawDescriptor &desc);

		void clear(const RenderTarget *target, const math::Vec4 color);

		void mapBuffer(Buffer *buffer);
		void unmapBuffer(Buffer *buffer);
		void copyData(Buffer *buffer, void *data, size_t size);
		void copyData(Buffer *buffer, size_t offset, void *data, size_t size);

		void setViewport(Viewport *viewport);
		// ----------

		// Special stuff
		Texture *createCubemapTextureFromTextures(TextureResource *textures[6]);

		DeviceData *getDeviceData() { return deviceData; }
	};

	RendererDevice *createRendererDevice(void *hwnd);

}
}

#endif