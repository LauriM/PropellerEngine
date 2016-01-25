// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "game/SpriteTestScene.h"

#include "engine/rtti/Class.h"
#include "engine/scene/Entity.h"
#include "engine/scene/TransformComponent.h"
#include "engine/GameInstance.h"

#include "engine/rtti/Class.h"
#include "engine/scene/Entity.h"
#include "engine/scene/TransformComponent.h"
#include "engine/physics/RigidBodyComponent.h"
#include "engine/GameInstance.h"

using namespace engine;
using namespace engine::scene;
using namespace engine::renderer;

namespace game {

	void SpriteTestScene::onSceneLoad(GameInstance *instance)
	{
#ifndef OS_LINUX
		for (unsigned i = 1; i < 2; ++i)
		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));
			entity->setName("SpriteTestEntity");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(float(i));

			entity->addComponent(transform);

			instance->getScene()->addEntity(entity);
		}

		unsigned scale = 1;

		for (int x = 0; x < 3; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));
				entity->setName("TestMeshEntity");

				TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

				transform->setPosition(math::Vec3(float(x) * 10, float(y) * 10, 30.f));
				transform->setScale(3.f);

				/*
				renderer::MeshComponent *mesh = rtti::dynamicCast<renderer::MeshComponent>(rtti::RTTI::generateSerializable("MeshComponent", instance->getContextData()));

				mesh->setModelName("test.PropellerModel");
				mesh->setDiffuse("taloTexture.png");
				mesh->setSpecular("taloTexture.png");
				mesh->setNormal("taloTexture.png");
				*/

				entity->addComponent(transform);
				//entity->addComponent(mesh);

				instance->getScene()->addEntity(entity);
				++scale;
			}
		}
#endif
	}

}
