// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "game/DummyScene.h"

#include "engine/rtti/Class.h"
#include "engine/scene/Entity.h"
#include "engine/scene/TransformComponent.h"
#include "engine/physics/RigidBodyComponent.h"
#include "engine/GameInstance.h"
#include "engine/renderer/MeshComponent.h"

using namespace engine;
using namespace engine::scene;
using namespace engine::renderer;
using namespace engine::physics;

namespace game {

	// Example 3D-scene
	void DummyScene::onSceneLoad(GameInstance *instance)
	{
#ifndef OS_ANDROID
		instance->getFileManager();
		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Hellknight");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(0.f, 0.f, 0.f));
			transform->setDirection(math::Vec3(0.f, 0.f, 0.f));
			transform->setScale(1.f);

			MeshComponent *mesh = rtti::dynamicCast<MeshComponent>(rtti::RTTI::generateSerializable("MeshComponent", instance->getContextData()));

			mesh->setModelName("hellknight.PropellerModel");
			mesh->setDiffuse("hellknight.png");
			mesh->setSpecular("hellknight_specular.png");
			mesh->setNormal("hellknight_normal.png");

			entity->addComponent(transform);
			entity->addComponent(mesh);

			instance->getScene()->addEntity(entity);
		}

		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Hellknight_buddy");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(50.f, 0.f, 150.f));
			transform->setDirection(math::Vec3(0.f, 2.f, 0.f));
			transform->setScale(1.f);

			MeshComponent *mesh = rtti::dynamicCast<MeshComponent>(rtti::RTTI::generateSerializable("MeshComponent", instance->getContextData()));

			mesh->setModelName("hellknight.PropellerModel");
			mesh->setDiffuse("hellknight.png");
			mesh->setSpecular("hellknight_specular.png");
			mesh->setNormal("hellknight_normal.png");

			entity->addComponent(transform);
			entity->addComponent(mesh);

			instance->getScene()->addEntity(entity);
		}

		for (unsigned i = 0; i < 35; ++i)
		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("ReflectiveBall");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(5.f + 0.1f * i, 20.f + (3 * i), 5.f - 0.1f * i));
			transform->setDirection(math::Vec3(0.f, 0.f, 0.f));
			transform->setScale(5.f);

			MeshComponent *mesh = rtti::dynamicCast<MeshComponent>(rtti::RTTI::generateSerializable("MeshComponent", instance->getContextData()));
			RigidBodyComponent *body = rtti::dynamicCast<RigidBodyComponent>(rtti::RTTI::generateSerializable("RigidBodyComponent", instance->getContextData()));

			body->setMass(1);
			body->setShape(COLLISION_SHAPE_SPREHE);

			mesh->setModelName("ball.PropellerModel");
			mesh->setDiffuse("ball_diffuse.png");
			mesh->setSpecular("ball_specular.png");
			mesh->setNormal("ball_normal.png");

			entity->addComponent(transform);
			entity->addComponent(mesh);
			entity->addComponent(body);

			instance->getScene()->addEntity(entity);
		}

		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Floor");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(0.f, 0.f, 0.f));
			transform->setDirection(math::Vec3(-1.5f, 0.f, 0.f));
			transform->setScale(5.f);

			MeshComponent *mesh = rtti::dynamicCast<MeshComponent>(rtti::RTTI::generateSerializable("MeshComponent", instance->getContextData()));

			mesh->setModelName("floor.PropellerModel");
			mesh->setDiffuse("floor.png");
			mesh->setSpecular("floor_specular.png");
			mesh->setNormal("floor_normal.png");
			mesh->setTextureScale(7);

			entity->addComponent(transform);
			entity->addComponent(mesh);

			instance->getScene()->addEntity(entity);
		}
#endif
	}

}
