// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.

#include "editorbackend/precompiled.h"

#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "editorbackend/modelviewer/ModelViewer.h"
#include "engine/GameInstance.h"

#include "game/Propeller.h"

#include "engine/component/ComponentHolder.h"
#include "engine/rtti/RTTI.h"
#include "engine/scene/TransformComponent.h"
#include "engine/renderer/MeshComponent.h"
#include "engine/renderer/RendererSystem.h"

#include "engine/console/Cvar.h"

namespace cvar {
	//EXTERN_CVAR(int, r_drawgrid);
}

namespace editor {

	REGISTER_CSHARPINSTANCE(ModelViewer);

	bool ModelViewer::init()
	{
		instance = new PrimaryGameInstance();

		registerEvent("update", this, &ModelViewer::update);
		registerEvent("initModelViewer", this, &ModelViewer::initModelViewer);

		// Movement input
		registerEvent("keyDown", this, &ModelViewer::keyDown);
		registerEvent("keyUp", this, &ModelViewer::keyUp);
		registerEvent("mouseDeltaInput", this, &ModelViewer::mouseDeltaInput);

		// Mesh events
		registerEvent("toggleWireframe", this, &ModelViewer::toggleWireframe);
		registerEvent("toggleGrid", this, &ModelViewer::toggleGrid);
		
		instance->getSystemManager()->stopSystem("IngameConsoleSystem");
		instance->getConsole()->execute("exec modelviewer.cfg");
		return true;
	}

	void ModelViewer::uninit()
	{
		instance->uninit();
		delete instance;
	}

	void ModelViewer::update()
	{
		instance->update();
	}

	void ModelViewer::toggleGrid()
	{
		/*
		if (*cvar::r_drawgrid)
		{
			cvar::r_drawgrid.set("0");
		}
		else
		{
			cvar::r_drawgrid.set("1");
		}
		*/
	}

	void ModelViewer::toggleWireframe()
	{
		renderer::MeshComponent *mesh = entity->findComponent<renderer::MeshComponent>();

		if (mesh->getWireframe())
		{
			mesh->setWireframe(false);
		}
		else
		{
			mesh->setWireframe(true);
		}
	}

	void ModelViewer::initModelViewer(String modelName, intptr_t hwnd)
	{
		instance->initializeRenderer(hwnd);
		instance->init();

		LOG_INFO("LOAD MODEL: " << modelName);

		entity = rtti::dynamicCast<engine::scene::Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));
		entity->setName("ModelEntity");

		engine::scene::TransformComponent *transform = rtti::dynamicCast<engine::scene::TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

		transform->setPosition(math::Vec3(0, 0, 0));
		transform->setDirection(math::Vec3(0, 1, 0));
		transform->setScale(1.f);

		renderer::MeshComponent *mesh = rtti::dynamicCast<renderer::MeshComponent>(rtti::RTTI::generateSerializable("MeshComponent", instance->getContextData()));

		mesh->setModelName(modelName);
		mesh->setDiffuse("taloTexture.png"); // TODO: CHECK THAT MODELS CAN BE RENDERED WITHOUT TEXTURES
		mesh->setNormal("taloTexture.png"); 
		mesh->setSpecular("taloTexture.png");
		mesh->setWireframe(false);

		entity->addComponent(transform);
		entity->addComponent(mesh);

		instance->getScene()->addEntity(entity);

		instance->sceneRefresh();

		instance->getConsole()->execute("setpos -0.8 -1.8 8");
	}

	void ModelViewer::keyUp(int keyCode)
	{
		instance->getInputSystem()->keyUp(engine::input::KeyCode(keyCode));
	}

	void ModelViewer::keyDown(int keyCode)
	{
		instance->getInputSystem()->keyDown(engine::input::KeyCode(keyCode));
	}

	void ModelViewer::mouseDeltaInput(float x, float y)
	{
		instance->getInputSystem()->axisMove(engine::input::MOUSE, x, y);
	}

}