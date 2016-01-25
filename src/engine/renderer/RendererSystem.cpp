// Copyright (c) Lauri Mäkinen 2014 - 21.0
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/RendererSystem.h"
#include "engine/console/Cvar.h"
#include "engine/resource/ResourceManager.h"
#include "engine/renderer/ShaderResource.h"
#include "engine/renderer/StateDescriptor.h"
#include "engine/renderer/DrawDescriptor.h"
#include "engine/renderer/ModelResource.h"
#include "engine/renderer/MeshComponent.h"
#include "engine/renderer/InputLayout.h"
#include "engine/renderer/SpriteComponent.h"
#include "engine/renderer/CameraSystem.h"
#include "engine/renderer/TextureResource.h"
#include "engine/scene/TransformComponent.h"
#include "engine/component/ComponentHolder.h"
#include "engine/renderer/LightComponent.h"
#include "engine/math/Vector.h"
#include "engine/math/Matrix.h"

#include "engine/sys/Scheduler.h"

namespace cvar {
	CVAR(int, r_width, 1000, true);
	CVAR(int, r_height, 800, true);
	CVAR(int, r_vsync, 1, false);

	EXTERN_CVAR(int, dimensions);
}

using namespace engine::math;

#ifndef NULLRENDERER

namespace engine {
namespace renderer {

	bool RendererSystem::init()
	{
		if (device != NULL)
		{
			delete device;
			LOG_INFO("[RendererSystem] Recreating the graphics context!");
		}

		device = createRendererDevice(hwnd);
		if (!device->init())
		{
			LOG_ERROR("[RendererSystem] Device initialization failed! Rendering stopping!");
			this->stop();
			return false;
		}

		mainViewport.leftX = 0;
		mainViewport.leftY = 0;
		mainViewport.width = *cvar::r_width;
		mainViewport.height	= *cvar::r_height;

		backbuffer = device->createBackbufferRenderTarget();
		lightBackBuffer = device->createRenderTarget(*cvar::r_width, *cvar::r_height);

		meshVertexShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("Mesh_vv.cso"));
		meshPixelShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("Mesh_p.cso"));

		spriteVertexShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("Sprite_vv.cso"));
		spritePixelShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("Sprite_p.cso"));
		spriteNoLightPixelShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("SpriteNoLight_p.cso"));

		light2DPixelShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("2DLight_p.cso"));

		skyboxPixelShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("SkyBox_p.cso"));
		skyboxVertexShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("SkyBox_vv.cso"));

		dummyVertexShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("Dummy_vv.cso"));
		dummyPixelShader = dynamic_cast<ShaderResource*>(resourceManager->getResourceByName("Dummy_p.cso"));

		InputLayoutDesc dummyLayoutDesc;
		dummyLayoutDesc.inputElementCount = 1;
		dummyLayoutDesc.inputElements[0].semantic = SEMANTIC_POSITION;
		dummyLayoutDesc.inputElements[0].inputFormat = INPUTFORMAT_FLOAT_XYZ;

		dummyInputLayout = device->createInputLayout(dummyLayoutDesc, dummyVertexShader);

		InputLayoutDesc spriteInputLayoutDesc;
		spriteInputLayoutDesc.inputElementCount = 2;
		spriteInputLayoutDesc.inputElements[0].semantic = SEMANTIC_POSITION;
		spriteInputLayoutDesc.inputElements[0].inputFormat = INPUTFORMAT_FLOAT_XYZ;
		spriteInputLayoutDesc.inputElements[1].semantic = SEMANTIC_TEXCOORD;
		spriteInputLayoutDesc.inputElements[1].inputFormat = INPUTFORMAT_FLOAT_XY;

		spriteInputLayout = device->createInputLayout(spriteInputLayoutDesc, spriteVertexShader);

		InputLayoutDesc meshILDesc;
		meshILDesc.inputElementCount = 3;
		meshILDesc.inputElements[0].semantic = SEMANTIC_POSITION;
		meshILDesc.inputElements[0].inputFormat = INPUTFORMAT_FLOAT_XYZ;
		meshILDesc.inputElements[1].semantic = SEMANTIC_TEXCOORD;
		meshILDesc.inputElements[1].inputFormat = INPUTFORMAT_FLOAT_XYZ;
		meshILDesc.inputElements[2].semantic = SEMANTIC_NORMAL;
		meshILDesc.inputElements[2].inputFormat = INPUTFORMAT_FLOAT_XYZ;

		meshInputLayout = device->createInputLayout(meshILDesc, meshVertexShader);

		StateDescriptor spriteStateDescriptor;
		spriteStateDescriptor.blendMode = BLEND_ADD;
		spriteStateDescriptor.cullMode = CULL_NONE;
		spriteStateDescriptor.fillMode = FILL_SOLID;
		spriteStateDescriptor.depthClipEnabled = false;
		spriteStateDescriptor.samplerState = DEFAULT_SAMPLER;

		spritePipeline = device->createRasterizerPipeline(&spriteStateDescriptor, spriteInputLayout, spriteVertexShader->shader, spritePixelShader->shader);

		spriteNoLightPipeline = device->createRasterizerPipeline(&spriteStateDescriptor, spriteInputLayout, spriteVertexShader->shader, spriteNoLightPixelShader->shader);

		StateDescriptor lightStateDescriptor;
		lightStateDescriptor.blendMode = BLEND_MAX;
		lightStateDescriptor.cullMode = CULL_NONE;
		lightStateDescriptor.fillMode = FILL_SOLID;
		lightStateDescriptor.depthClipEnabled = false;
		lightStateDescriptor.samplerState = DEFAULT_SAMPLER;

		light2DPipeline = device->createRasterizerPipeline(&lightStateDescriptor, spriteInputLayout, spriteVertexShader->shader, light2DPixelShader->shader);

		StateDescriptor skyboxStateDescriptor;
		skyboxStateDescriptor.blendMode = BLEND_NONE;
		skyboxStateDescriptor.cullMode = CULL_NONE;
		skyboxStateDescriptor.fillMode = FILL_SOLID;
		skyboxStateDescriptor.depthClipEnabled = true;
		skyboxStateDescriptor.samplerState = DEFAULT_SAMPLER;

		skyboxPipeline = device->createRasterizerPipeline(&skyboxStateDescriptor, spriteInputLayout, skyboxVertexShader->shader, skyboxPixelShader->shader);

		StateDescriptor meshStateDescriptor;
		meshStateDescriptor.blendMode = BLEND_NONE;
		meshStateDescriptor.cullMode = CULL_BACK;
		meshStateDescriptor.fillMode = FILL_SOLID;
		meshStateDescriptor.depthClipEnabled = true;
		meshStateDescriptor.samplerState = DEFAULT_SAMPLER;

		meshPipeline = device->createRasterizerPipeline(&meshStateDescriptor, meshInputLayout, meshVertexShader->shader, meshPixelShader->shader);

		StateDescriptor dummyState;
		dummyState.blendMode = BLEND_NONE;
		dummyState.cullMode = CULL_NONE;
		dummyState.fillMode = FILL_SOLID;
		dummyState.depthClipEnabled = false;
		dummyState.samplerState = DEFAULT_SAMPLER;

		dummyLine = device->createRasterizerPipeline(&dummyState, dummyInputLayout, dummyVertexShader->shader, dummyPixelShader->shader);

		// Create buffers for quad
		spriteVertexBuffer = device->createBuffer(BUFFERTYPE_VERTEX, sizeof(float) * 20, BUFFERUSAGE_DYNAMIC); //TODO: HACK QQQ TOO LARGE !
		spriteIndexBuffer = device->createBuffer(BUFFERTYPE_INDEX, sizeof(uint16_t) * 6, BUFFERUSAGE_DYNAMIC);

		// Will contain all the constant buffers used
		//TODO: Better management of the constant buffers!
		meshConstantBuffer = device->createBuffer(BUFFERTYPE_CONSTANT, 16 * 20, BUFFERUSAGE_DYNAMIC); //TODO: fix the size for this buffer ! //TODO: is this even in use ?!?
		lightConstantBuffer = device->createBuffer(BUFFERTYPE_CONSTANT, 48, BUFFERUSAGE_DYNAMIC);
		pixelConstantBuffer = device->createBuffer(BUFFERTYPE_CONSTANT, 48, BUFFERUSAGE_DYNAMIC);

		commandListMutex = sys::createMutex();

		// HACK QQQ
		debugLightPos = Vec3(10.f, -80.f, 140.f);
		dir = 7;

		skyboxTexture = dynamic_cast<TextureResource*>(resourceManager->getResourceByName("skybox.dds"));

		return true;
	}

	void RendererSystem::uninit()
	{
		LOG_WARNING("[RendererSystem] uninit() not fully implemented!");

		device->uninit();
	}

	void RendererSystem::update(float delta)
	{
		PROFILE;

		device->beginFrame();

		device->clear(lightBackBuffer, math::Vec4(0.f, 0.f, 0.f, 0.f));
		device->clear(backbuffer, math::Vec4(0.f, 0.f, 0.f, 0.f));

		// TODO: Choose from a 2D and 3D pipeline, or both ! Based on a cvar or something
		// TODO: light culling is missing!

		//HACK: Ultimate hack way to get the correct lenght. Longer side * unit size (one pixel on screen is 2 units in game for some reason) added 0.2f for good measure.
#ifdef OS_ANDROID
		cullDistance = std::max(*cvar::r_width, *cvar::r_height) * 2.2f;
#else
		cullDistance = max(*cvar::r_width, *cvar::r_height) * 2.2f;
#endif

		if (*cvar::dimensions == 2)
		{
#if 1
			processSpriteComponentsNoLight();
#else
			process2DLights();
			processSpriteComponents();
#endif
		}

		if (*cvar::dimensions == 3)
		{
			//processSkyBox(); // TODO: disabled because of depth issues
			processMeshComponents();
		}

		device->endFrame();
	}

	void RendererSystem::dummyDraw()
	{
		device->setBackbuffer(backbuffer);
		device->setViewport(&mainViewport);

		float vertexData[] = {
			-1, 1, 0.f,
			-1, -0.5, 0.f,
			1, -1, 0.f,
			1, 1, 0.f,
		};

		uint16_t indexData[] = {
			2, 1, 0,
			0, 3, 2,
		};

		device->mapBuffer(spriteVertexBuffer);
		device->copyData(spriteVertexBuffer, &vertexData, sizeof(vertexData));
		device->unmapBuffer(spriteVertexBuffer);

		// TODO: Index buffers could be done once!
		device->mapBuffer(spriteIndexBuffer);
		device->copyData(spriteIndexBuffer, &indexData, sizeof(indexData));
		device->unmapBuffer(spriteIndexBuffer);

		device->setVertexBuffer(spriteVertexBuffer);
		device->setIndexBuffer(spriteIndexBuffer);

		device->setPipeline(dummyLine);

		DrawDescriptor desc;
		desc.topology = PRIMITIVETOPOLOGY_TRIANGLELIST;
		desc.drawCount = 6;

		device->draw(desc);
	}

	void RendererSystem::processSkyBox()
	{
		device->setPipeline(skyboxPipeline);
		device->setBackbuffer(backbuffer);
		device->setViewport(&mainViewport);

		// Draw using fullscreen quad ( HANDLE THIS BETTER LATER )

		// Fullscreen quad
		float vertexData[] = {
			-1, 1, 0.f,  0.f, 1.f,
			-1, -1, 0.f,  0.f, 0.f,
			1, -1, 0.f,  1.f, 0.f,
			1, 1,  0.f,  1.f, 1.f,
		};

		uint16_t indexData[] = {
			2, 1, 0,
			0, 3, 2,
		};;

		struct ConstantData
		{
			Matrix4x4 cameraMatrix;
			Matrix4x4 projectionMatrix;
		} cData;

		cData.cameraMatrix = cameraSystem->getRotation().getMatrix();

#ifdef D3D11
		cData.projectionMatrix = Matrix4x4::getPerspective(1.39f, float(*cvar::r_width) / float(*cvar::r_height), 1.f, 3000.f, true);
#else
		Matrix4x4 projectionMatrix = Matrix4x4::getPerspective(1.39f, float(*cvar::r_width) / float(*cvar::r_height), 1.f, 3000.f, false);
#endif

		device->mapBuffer(meshConstantBuffer); // TODO: rename meshConstant to "genericConstant" or something
		device->copyData(meshConstantBuffer, &cData, sizeof(cData));
		device->unmapBuffer(meshConstantBuffer);

		device->mapBuffer(spriteVertexBuffer);
		device->copyData(spriteVertexBuffer, &vertexData, sizeof(vertexData));
		device->unmapBuffer(spriteVertexBuffer);

		// TODO: Index buffers could be done once!
		device->mapBuffer(spriteIndexBuffer);
		device->copyData(spriteIndexBuffer, &indexData, sizeof(indexData));
		device->unmapBuffer(spriteIndexBuffer);

		device->setVertexBuffer(spriteVertexBuffer);
		device->setIndexBuffer(spriteIndexBuffer);
		device->setPSTextureResource(0, skyboxTexture->getTexture());
		device->setPSTextureResource(1, lightBackBuffer);
		device->setVSConstantBuffer(meshConstantBuffer, 0);

		DrawDescriptor desc;
		desc.topology = PRIMITIVETOPOLOGY_TRIANGLELIST;
		desc.drawCount = 6;

		device->draw(desc);
	}

	void RendererSystem::processMeshComponents()
	{
		PROFILE;

		device->setPipeline(meshPipeline);
		device->setBackbuffer(backbuffer);

		for (unsigned i = 0; i < components.size(); ++i)
		{
			MeshComponent *mesh = rtti::dynamicCast<MeshComponent>(components[i]);

			if (mesh == NULL)
				continue;

			handleMeshComponent(mesh);
		}
	}

	void RendererSystem::handleMeshComponent(MeshComponent *meshComponent)
	{
		device->setPipeline(meshPipeline);
		device->setBackbuffer(backbuffer);
		device->setViewport(&mainViewport);

		/*
		if (meshComponent->getWireframe())
			device->setRasterState(RASTERSTATE_3D_WIREFRAME);
		else
			device->setRasterState(RASTERSTATE_3D);
			*/

		// TODO: handle error cases when resources are missing
		if (meshComponent->getDiffuseResource() != NULL)
			device->setPSTextureResource(0, meshComponent->getDiffuseResource()->getTexture());
		else
			LOG_WARNING("diffuse map missing for a mesh!");

		if (meshComponent->getNormalResource() != NULL)
			device->setPSTextureResource(1, meshComponent->getNormalResource()->getTexture());
		else
			LOG_WARNING("normal map missing for a mesh!");

		if (meshComponent->getSpecularResource() != NULL)
			device->setPSTextureResource(2, meshComponent->getSpecularResource()->getTexture());
		else
			LOG_WARNING("specular map missing for a mesh!");

		device->setPSTextureResource(3, skyboxTexture->getTexture());

		struct VertexConstantData
		{
			Matrix4x4 worldMatrix;
			Matrix4x4 cameraMatrix;
			Matrix4x4 projectionMatrix;
			Vec3 cameraPos;
			Vec3 debugLightPos;
		} cData;

		struct PixelConstantData
		{
			float textureScale;
		} pixelData;

		pixelData.textureScale = meshComponent->getTextureScale();

		scene::TransformComponent *transform = meshComponent->getParent()->findComponent<scene::TransformComponent>();
		math::Vec3 rotation = transform->getDirection();
		Matrix4x4 rotationX = Matrix4x4::getRotationX(rotation.x);
		Matrix4x4 rotationY = Matrix4x4::getRotationY(rotation.y);
		Matrix4x4 rotationZ = Matrix4x4::getRotationZ(rotation.z);

		Matrix4x4 scale = Matrix4x4::getScale(transform->getScale());
		Matrix4x4 rotationMatrix = rotationX;
		rotationMatrix *= rotationY;
		rotationMatrix *= rotationZ;

		Matrix4x4 translationMatrix = Matrix4x4::getTranslation(transform->getPosition());

#ifdef D3D11
		cData.projectionMatrix = Matrix4x4::getPerspective(1.39f, float(*cvar::r_width) / float(*cvar::r_height), 1.f, 3000.f, true);
#else
		cData.projectionMatrix = Matrix4x4::getPerspective(1.39f, float(*cvar::r_width) / float(*cvar::r_height), 1.f, 3000.f, false);
#endif

		cData.cameraMatrix = cameraSystem->getMatrix();

		cData.worldMatrix = scale;
		cData.worldMatrix *= rotationMatrix;
		cData.worldMatrix *= translationMatrix;

		cData.cameraPos = cameraSystem->getPosition();

		if (debugLightPos.y > 200)
			dir = -1;

		if (debugLightPos.y < -200)
			dir = 1;

		debugLightPos += Vec3(0, dir, 0);
		//		debugLightPos = Vec3(125, -200, 50);

		cData.debugLightPos = debugLightPos;

		device->mapBuffer(pixelConstantBuffer);
		device->copyData(pixelConstantBuffer, &pixelData, sizeof(pixelData));
		device->unmapBuffer(pixelConstantBuffer);

		device->mapBuffer(meshConstantBuffer);
		device->copyData(meshConstantBuffer, &cData, sizeof(cData));
		device->unmapBuffer(meshConstantBuffer);

		device->setIndexBuffer(meshComponent->getModelResource()->indexBuffer.getPtr());
		device->setVertexBuffer(meshComponent->getModelResource()->vertexBuffer.getPtr());
		device->setVSConstantBuffer(meshConstantBuffer, 0);
		device->setPSConstantBuffer(pixelConstantBuffer, 0);

		DrawDescriptor drawDesc;
		drawDesc.drawCount = meshComponent->getModelResource()->indicesCount;
		drawDesc.topology = PRIMITIVETOPOLOGY_TRIANGLELIST;

		device->draw(drawDesc);
	}

	struct SpriteJobData
	{
		RendererSystem *sys;
		SpriteComponent *comp;
	};

	// Deprecrated (?) multithreaded function
	void processSpriteJob(void *userdata)
	{
		SpriteJobData *data = (SpriteJobData*)userdata;

		data->sys->handleSpriteComponent(data->comp);

		TOMBSTONE(16_10_2015);
	}

	void RendererSystem::processSpriteComponents()
	{
		PROFILE;

		for (unsigned i = 0; i < spriteComponents.getSize(); ++i)
			handleSpriteComponent(spriteComponents[i]);
	}

	void RendererSystem::process2DLights()
	{
		PROFILE;

		for (unsigned i = 0; i < lightComponents.getSize(); ++i)
			handle2DLightComponent(lightComponents[i]);
	}

	void RendererSystem::handle2DLightComponent(LightComponent *lightComponent)
	{
		scene::TransformComponent *transform = lightComponent->getParent()->findComponent<scene::TransformComponent>();
		math::Vec2 lightPos = transform->getPosition();

		device->setBackbuffer(lightBackBuffer);
		device->setViewport(&mainViewport);

		// Draw using fullscreen quad ( HANDLE THIS BETTER LATER )
		Vec2 vert1(-1, 1);
		Vec2 vert2(-1, -1);
		Vec2 vert3(1, -1);
		Vec2 vert4(1, 1);

		float vertexData[] = {
			vert1.x, vert1.y, 0.f, 0.f, 1.f,
			vert2.x, vert2.y, 0.f, 0.f, 0.f,
			vert3.x, vert3.y, 0.f, 1.f, 0.f,
			vert4.x, vert4.y, 0.f, 1.f, 1.f,
		};

		uint16_t indexData[] = {
			0, 1, 2,
			0, 3, 2,
		};

		struct ConstantData
		{
			math::Vec2 pos;
			math::Vec3 color;
			float distance;
		} cData;

		cData.color = lightComponent->getColor();
		cData.distance = lightComponent->getDistance();

		cData.pos = (math::Vec2(cameraSystem->getPosition()) + lightPos) / 2;
		cData.pos.x += (*cvar::r_width / 2);
		cData.pos.y += (*cvar::r_height / 2);

		// From world space to screenspace
		cData.pos.x /= *cvar::r_width;
		cData.pos.y /= *cvar::r_height;

		device->mapBuffer(lightConstantBuffer);
		device->copyData(lightConstantBuffer, &cData, sizeof(cData));
		device->unmapBuffer(lightConstantBuffer);

		device->mapBuffer(spriteVertexBuffer);
		device->copyData(spriteVertexBuffer, &vertexData, sizeof(vertexData));
		device->unmapBuffer(spriteVertexBuffer);

		// TODO: Index buffers could be done once!
		device->mapBuffer(spriteIndexBuffer); //TODO: this buffer doesn't change in size! Optimize it to be static
		device->copyData(spriteIndexBuffer, &indexData, sizeof(indexData));
		device->unmapBuffer(spriteIndexBuffer);

		device->setVertexBuffer(spriteVertexBuffer);
		device->setIndexBuffer(spriteIndexBuffer);
		device->setPSConstantBuffer(lightConstantBuffer, 0);

		device->setPipeline(light2DPipeline);

		DrawDescriptor draw;
		draw.topology = PRIMITIVETOPOLOGY_TRIANGLELIST;
		draw.drawCount = 6;
		device->draw(draw);
	}

	/*
	void RendererSystem::processSpriteComponents()
	{
		sys::Timer timer;
		timer.start();
		device->clear(lightBackBuffer, math::Vec4(0.f, 0.f, 0.f, 0.f));
		device->setPipeline(spritePipeline);
		device->setBackbuffer(backbuffer);

		for (unsigned i = 0; i < components.size(); ++i)
		{
			SpriteComponent *sprite = rtti::dynamicCast<SpriteComponent>(components[i]);

			if (sprite == NULL)
				continue;

			handleSpriteComponent(sprite);
		}
		DEBUG_PRINT(timer.getTimeInMicroSeconds());
	}
	*/

	void RendererSystem::handleSpriteComponent(SpriteComponent *component)
	{
		PROFILE;
		if (component->getDrawEnabled() == false)
			return; // Draw is disabled for this sprite!

		device->setBackbuffer(backbuffer);
		device->setViewport(&mainViewport);

		struct SpriteConstantData
		{
			float r_width;
			float r_height;
			math::Vec4 ambientLight;
		} spriteData;

		//TODO: OPTMIZATION: Make this constant data _ACTUALLY CONSTANT_ doesn't need to change at all between frames
		spriteData.r_width = float(*cvar::r_width);
		spriteData.r_height = float(*cvar::r_height);
		spriteData.ambientLight = ambientLight;

		TextureResource *resource = component->getTextureResource();

		// apply transformation of the object
		scene::TransformComponent *transform = component->getParent()->findComponent<scene::TransformComponent>();
		math::Vec3 pos = transform->getPosition();

		float angle = math::Vec2(transform->getDirection()).getAngle();

		if (component->getDrawToScreenCoordinates() == false)
			pos += math::Vec2(cameraSystem->getPosition()); // vec2 to filter away the z, z controls the depth

		pos.y /= *cvar::r_height; //TODO: add a "pixels to meters scale" or something !
		pos.x /= *cvar::r_width;

		Vec2 vert1(-1, 1);
		Vec2 vert2(-1, -1);
		Vec2 vert3(1, -1);
		Vec2 vert4(1, 1);

		float sizey = resource->getHeight() * transform->getScale() * component->getHeightScale() / *cvar::r_height;
		float sizex = resource->getWidth() * transform->getScale() * component->getWidthScale() / *cvar::r_width;

		math::Matrix2x2 scale(sizex, 0, 0, sizey);

		vert1 = scale * vert1;
		vert2 = scale * vert2;
		vert3 = scale * vert3;
		vert4 = scale * vert4;

		math::Matrix2x2 rotation(cos(angle), sin(angle), -sin(angle), cos(angle));

		vert1 = rotation * vert1;
		vert2 = rotation * vert2;
		vert3 = rotation * vert3;
		vert4 = rotation * vert4;

		float z = transform->getPosition().z;

		float vertexData[] = {
			vert1.x + pos.x, vert1.y + pos.y, z, 0.f, 1.f,
			vert2.x + pos.x, vert2.y + pos.y, z, 0.f, 0.f,
			vert3.x + pos.x, vert3.y + pos.y, z, 1.f, 0.f,
			vert4.x + pos.x, vert4.y + pos.y, z, 1.f, 1.f,
		};

		uint16_t indexData[] = {
			0, 1, 2,
			0, 3, 2,
		};

		device->mapBuffer(pixelConstantBuffer);
		device->copyData(pixelConstantBuffer, &spriteData, sizeof(spriteData));
		device->unmapBuffer(pixelConstantBuffer);

		device->mapBuffer(spriteVertexBuffer);
		device->copyData(spriteVertexBuffer, &vertexData, sizeof(vertexData));
		device->unmapBuffer(spriteVertexBuffer);

		// TODO: Index buffers could be done once!
		device->mapBuffer(spriteIndexBuffer);
		device->copyData(spriteIndexBuffer, &indexData, sizeof(indexData));
		device->unmapBuffer(spriteIndexBuffer);

		device->setVertexBuffer(spriteVertexBuffer);
		device->setIndexBuffer(spriteIndexBuffer);
		device->setPSTextureResource(0, resource->getTexture());
		device->setPSTextureResource(1, lightBackBuffer);
		device->setPSConstantBuffer(pixelConstantBuffer, 0);

		device->setPipeline(spritePipeline);

		DrawDescriptor desc;
		desc.topology = PRIMITIVETOPOLOGY_TRIANGLELIST;
		desc.drawCount = 6;

		device->draw(desc);
	}

	void RendererSystem::handleSpriteNoLight(SpriteComponent *component)
	{
		PROFILE;

		if (component->getDrawEnabled() == false)
			return; // Draw is disabled for this sprite!

		scene::TransformComponent *transform = component->getParent()->findComponent<scene::TransformComponent>();

		math::Vec3 dist = cameraSystem->getPosition();

		dist += transform->getPosition();
		dist.z = 0;

		// "hack"
		if (dist.getLenght() > cullDistance)
			if (component->getDrawToScreenCoordinates() == false) // also check that its not something to be drawn on the screen
				if (component->getDisableCullCheck() == false) // culling can also be disabled manually
					return; // Cull it! Not needed!

#ifdef D3D11
		device->setPipeline(spriteNoLightPipeline);
		device->setBackbuffer(backbuffer);
		device->setViewport(&mainViewport);
#endif

		TextureResource *resource = component->getTextureResource();

		// apply transformation of the object
		math::Vec3 pos = transform->getPosition();

		float angle = math::Vec2(transform->getDirection()).getAngle();

		if (component->getDrawToScreenCoordinates() == false)
			pos += math::Vec2(cameraSystem->getPosition()); // vec2 to filter away the z, z controls the depth

		pos.y /= *cvar::r_height; //TODO: add a "pixels to meters scale" or something !
		pos.x /= *cvar::r_width;

		Vec2 vert1(-1, 1);
		Vec2 vert2(-1, -1);
		Vec2 vert3(1, -1);
		Vec2 vert4(1, 1);

		device->setBackbuffer(backbuffer);
		device->setViewport(&mainViewport);
		math::Matrix2x2 rotation(cos(angle), sin(angle), -sin(angle), cos(angle));

		vert1 = rotation * vert1;
		vert2 = rotation * vert2;
		vert3 = rotation * vert3;
		vert4 = rotation * vert4;

		float sizey = resource->getHeight() * transform->getScale() / *cvar::r_height;
		float sizex = resource->getWidth() * transform->getScale() / *cvar::r_width;

		math::Matrix2x2 scale(sizex, 0, 0, sizey);

		vert1 = scale * vert1;
		vert2 = scale * vert2;
		vert3 = scale * vert3;
		vert4 = scale * vert4;

		float z = transform->getPosition().z;

		float vertexData[] = {
			vert1.x + pos.x, vert1.y + pos.y, z, 0.f, 1.f,
			vert2.x + pos.x, vert2.y + pos.y, z, 0.f, 0.f,
			vert3.x + pos.x, vert3.y + pos.y, z, 1.f, 0.f,
			vert4.x + pos.x, vert4.y + pos.y, z, 1.f, 1.f,
		};

		uint16_t indexData[] = {
			0, 1, 2,
			0, 3, 2,
		};

		device->mapBuffer(spriteVertexBuffer);
		device->copyData(spriteVertexBuffer, &vertexData, sizeof(vertexData));
		device->unmapBuffer(spriteVertexBuffer);

		// TODO: Index buffers could be done once!
		device->mapBuffer(spriteIndexBuffer);
		device->copyData(spriteIndexBuffer, &indexData, sizeof(indexData));
		device->unmapBuffer(spriteIndexBuffer);

		device->setVertexBuffer(spriteVertexBuffer);
		device->setIndexBuffer(spriteIndexBuffer);
		device->setPSTextureResource(0, resource->getTexture());

#ifdef GL2
		device->setPipeline(spriteNoLightPipeline);
#endif

		DrawDescriptor desc;
		desc.topology = PRIMITIVETOPOLOGY_TRIANGLELIST;
		desc.drawCount = 6;

		device->draw(desc);
	}

	void RendererSystem::processSpriteComponentsNoLight()
	{
		PROFILE;

		for (unsigned i = 0; i < spriteComponents.getSize(); ++i)
			handleSpriteNoLight(spriteComponents[i]);

	}

	// Go trough all components with assets and reload them
	void RendererSystem::reloadAssets()
	{
		//TODO: Mesh stuff is missing !!
		LOG_INFO("[RendererSystem] Reloading sprite assets...");

		for (unsigned i = 0; i < spriteComponents.getSize(); ++i)
			spriteComponents[i]->reloadTexture();

		LOG_INFO("[RendererSystem] Asset reloading done!");
	}

}
}

#endif
