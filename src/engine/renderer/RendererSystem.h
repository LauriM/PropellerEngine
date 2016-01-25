// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_RENDERERSYSTEM_H
#define ENGINE_RENDERER_RENDERERSYSTEM_H

#include "engine/SystemBase.h"

#include "engine/renderer/RendererBackend.h"
#include "engine/renderer/RendererDevice.h"
#include "engine/sys/Thread.h"
#include "engine/sys/Mutex.h"
#include "engine/util/Array.h"
#include "engine/renderer/Viewport.h"

PROPELLER_FORWARD_DECLARE_2(engine, resource, ResourceManager);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, ShaderResource);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, SpriteComponent);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, LightComponent);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, TextureResource);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, MeshComponent);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, CameraSystem);

namespace engine {
namespace renderer {

	struct Pipeline;

	class RendererSystem : public SystemBase
	{
	private:
		CameraSystem *cameraSystem;
		void *hwnd;
		RendererDevice *device;
		resource::ResourceManager *resourceManager;

		// Viewports
		Viewport mainViewport;

		// InputLayouts
		InputLayout *spriteInputLayout;
		InputLayout *meshInputLayout;
		InputLayout *dummyInputLayout;

		// RenderTargets
		RenderTarget *backbuffer;
		RenderTarget *lightBackBuffer; // 2D light effects buffer

		// Shaders
		ShaderResource *meshVertexShader;
		ShaderResource *meshPixelShader;
		ShaderResource *spriteVertexShader;
		ShaderResource *spritePixelShader;
		ShaderResource *spriteNoLightPixelShader;
		ShaderResource *light2DPixelShader;
		ShaderResource *skyboxPixelShader;
		ShaderResource *skyboxVertexShader;
		ShaderResource *dummyVertexShader;
		ShaderResource *dummyPixelShader;

		// Pipelines
		Pipeline *light2DPipeline;
		Pipeline *spritePipeline;
		Pipeline *spriteNoLightPipeline;
		Pipeline *meshPipeline;
		Pipeline *skyboxPipeline;
		Pipeline *dummyLine;

		// Buffers
		Buffer *spriteIndexBuffer;
		Buffer *spriteVertexBuffer;

		Buffer *meshConstantBuffer;
		Buffer *pixelConstantBuffer;
		Buffer *lightConstantBuffer;

		// Mutex
		sys::Mutex *commandListMutex;

		// Component lists
		util::Array<SpriteComponent*> spriteComponents;
		util::Array<LightComponent*> lightComponents;

		// Debug
		math::Vec3 debugLightPos;
		float dir;
		TextureResource *skyboxTexture;

		// Stuff
		math::Vec4 ambientLight;

		// Recalculated each frame or something, last minute circle cull hack thing, ignore
		float cullDistance;

	public:
		RendererSystem(void *hwnd, resource::ResourceManager *resourceManager, CameraSystem *cameraSystem)
			: hwnd(hwnd)
			, resourceManager(resourceManager)
			, cameraSystem(cameraSystem)
			, ambientLight(0.f, 0.f, 0.f, 0.f)
			, device(NULL)
		{ }

		void setHWND(intptr_t h) { hwnd = (void*)h; }

	private:

		void handleSpriteNoLight(SpriteComponent *component);
		void processSpriteComponentsNoLight();

	public:

		//TODO: should these really be public ? 

		void processSkyBox();
		void processSpriteComponents();
		void processMeshComponents();
		void process2DLights();


		void handle2DLightComponent(LightComponent *component);
		void handleSpriteComponent(SpriteComponent *component);
		void handleMeshComponent(MeshComponent *component);
		void dummyDraw();

		// Trigger reloading on all components assets
		void reloadAssets();

		// Set 2D ambientlight
		void setAmbientLight(math::Vec4 l) { ambientLight = l; }

		const String getName() { return "RendererSystem"; }

		const bool isGameplaySystem() { return false; }
		const bool isRendererSystem() { return true; }

		bool init();
		void uninit();
		void update(float delta);

		// TODO: A better way to handle adding/removal of multiple components
		void addSpriteComponent(SpriteComponent *comp) { spriteComponents.push(comp); }

		void removeSpriteComponent(SpriteComponent *comp)
		{
			PROFILE;
			for (unsigned i = 0; i < spriteComponents.getSize(); ++i)
			{
				if (spriteComponents[i] == comp)
				{
					spriteComponents.remove(i);
					return;
				}
			}

			LOG_WARNING("[RendererSystem] Failed to remove SpriteComponent!");
		}

		void addLightComponent(LightComponent *comp) { lightComponents.push(comp); }

		void removeLightComponent(LightComponent *comp)
		{
			PROFILE;
			for (unsigned i = 0; i < lightComponents.getSize(); ++i)
			{
				if (lightComponents[i] == comp)
				{
					lightComponents.remove(i);
					return;
				}
			}

			LOG_WARNING("[RendererSystem] Failed to remove SpriteComponent!");
		}

		RendererDevice *getDevice() { return device; }
	};

}
}

#endif
