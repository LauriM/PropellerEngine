// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "game/PhysicsTestScene.h"

#include "game/pickup/PickupComponent.h"
#include "engine/scene/Entity.h"
#include "engine/scene/TransformComponent.h"
#include "engine/GameInstance.h"
#include "engine/physics/Box2DRigidBodyComponent.h"
#include "engine/physics/Box2DCharacterComponent.h"
#include "game/player/PlayerInputComponent.h"
#include "engine/scene/CameraComponent.h"
#include "engine/renderer/SpriteComponent.h"
#include "engine/renderer/LightComponent.h"
#include "engine/renderer/RendererSystem.h"

using namespace engine;
using namespace engine::scene;

namespace game {

	// Example 2D physics scene.
	void PhysicsTestScene::onSceneLoad(GameInstance *instance)
	{
		ContextData *context = instance->getContextData();

		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("background");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(0.f, 0.f, LAYER_BACKGROUND_0));
			transform->setDirection(math::Vec3(0.0f, 0.0f, 1.f));
			transform->setScale(150.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("grass.png");
			sprite->setDisableCullCheck(true);

			entity->addComponent(transform);
			entity->addComponent(sprite);

			instance->getScene()->addEntity(entity);
		}

		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("block");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(0.f, 50.f, LAYER_BACKGROUND_0));
			transform->setDirection(math::Vec3(-0.5f, 0.5f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("biggrass.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			phys->setMass(5);
			phys->setFriction(1.f);
			phys->setDensity(1.0f);
			phys->setRestitution(0.8f);
			phys->setKinematic(true);
			phys->setGroup(physics::BOX2D_GROUP_LEVEL);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);

			instance->getScene()->addEntity(entity);
		}


		for (unsigned i = 0; i < 2000; ++i)
		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("block");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(150.f + i * 250.f, 50.f, LAYER_BACKGROUND_0));
			transform->setDirection(math::Vec3(-0.5f, 0.5f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("biggrass.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			phys->setMass(5);
			phys->setFriction(1.f);
			phys->setDensity(1.0f);
			phys->setRestitution(0.8f);
			phys->setKinematic(true);
			phys->setGroup(physics::BOX2D_GROUP_LEVEL);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);

			instance->getScene()->addEntity(entity);
		}

		unsigned l = 10;
		for (unsigned i = 0; i < 10; ++i)
		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Object");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(0.f, 750.f + 150.f * i, LAYER_OBJECT_1));

			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("isopropelli.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			game::PickupComponent *pickup = rtti::dynamicCast<game::PickupComponent>(rtti::RTTI::generateSerializable("PickupComponent", instance->getContextData()));

			phys->setMass(10);
			phys->setKinematic(false);
			phys->setFriction(0.8f);
			phys->setDensity(1.f);
			//phys->setGroup(physics::BOX2D_GROUP_NONSOLID_OBJECT);
			phys->setSizeY(64);
			phys->setSizeX(84);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);
			entity->addComponent(pickup);

			--l;
			if (l == 0)
			{
				/*
				renderer::LightComponent *light = rtti::generate<renderer::LightComponent>(instance->getContextData());

				light->setColor(math::Vec3(0.0f, 0.0f, 1.f));
				light->setDistance(10.f);

				sprite->setWidthScale(5.f);

				entity->addComponent(light);
				l = 5;
				*/
			}

			instance->getScene()->addEntity(entity);
		}


		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Ground2");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(150.f, -450.f, LAYER_BACKGROUND_2));
			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("hellknight.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			phys->setMass(5);
			phys->setFriction(1.f);
			phys->setDensity(1.0f);
			phys->setKinematic(true);
			phys->setGroup(physics::BOX2D_GROUP_LEVEL);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);

			instance->getScene()->addEntity(entity);
		}


		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Ground3");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(850.f, 0.f, LAYER_BACKGROUND_2));
			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("hellknight.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			phys->setFriction(1.f);
			phys->setMass(5);
			phys->setDensity(1.0f);
			phys->setKinematic(true);
			phys->setGroup(physics::BOX2D_GROUP_LEVEL);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);

			instance->getScene()->addEntity(entity);
		}

		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Ground");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(850.f, 550.f, LAYER_BACKGROUND_2));
			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("hellknight.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			phys->setFriction(1.f);
			phys->setMass(5);
			phys->setDensity(1.0f);
			phys->setKinematic(true);
			phys->setGroup(physics::BOX2D_GROUP_LEVEL);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);

			instance->getScene()->addEntity(entity);
		}


		{
			Entity *entity = rtti::generate<Entity>(instance->getContextData());
			entity->setName("Player");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(150.f, 1750.f, LAYER_OBJECT_1));

			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("testcube.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			phys->setMass(5);
			phys->setFriction(0.5f);
			phys->setDensity(1.0f);
			phys->setKinematic(false);
			phys->setBodyShape(physics::SHAPE_CIRCLE);
			phys->setFixedRotation(true);
			phys->setGroup(physics::BOX2D_GROUP_SOLID_OBJECT);

			player::PlayerInputComponent *playerInput = rtti::dynamicCast<player::PlayerInputComponent>(rtti::RTTI::generateSerializable("PlayerInputComponent", instance->getContextData()));

#ifndef NULLRENDERER
			scene::CameraComponent *camera = rtti::dynamicCast<scene::CameraComponent>(rtti::RTTI::generateSerializable("CameraComponent", instance->getContextData()));
#endif

//			renderer::LightComponent *light = rtti::generate<renderer::LightComponent>(instance->getContextData());
//			light->setColor(math::Vec3(1.0f, 1.0f, 1.f));
//			light->setDistance(50);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);
			entity->addComponent(playerInput);
//			entity->addComponent(light);
#ifndef NULLRENDERER
			entity->addComponent(camera);
#endif

			// Create parent Entity
			scene::Entity *ent = rtti::generate<scene::Entity>(instance->getContextData());
			scene::TransformComponent *ent2_transform = rtti::generate<scene::TransformComponent>(instance->getContextData());
			renderer::SpriteComponent *ent2_sprite = rtti::generate<renderer::SpriteComponent>(instance->getContextData());

			// 0.3f to move it up a bit
			ent2_transform->setPosition(math::Vec3(75.f, 75.f, LAYER_OBJECT_2));
			ent2_sprite->setTexture("testcube.png");

			ent->addComponent(ent2_transform);
			ent->addComponent(ent2_sprite);

			// PARENTING
			ent->setParentEntity(entity);

			instance->getScene()->addEntity(entity);
			instance->getScene()->addEntity(ent);

			ent2_transform->getPosition();

#ifndef NULLRENDERER
			camera->setActive(true);
#endif
			if (instance->getContextData()->rendererSystem != NULL)
				instance->getContextData()->rendererSystem->setAmbientLight(math::Vec4(0.3f, 0.3f, 0.3f, 0.3f));
		}




		{
			Entity *entity = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", instance->getContextData()));;
			entity->setName("Ground4");

			TransformComponent *transform = rtti::dynamicCast<TransformComponent>(rtti::RTTI::generateSerializable("TransformComponent", instance->getContextData()));

			transform->setPosition(math::Vec3(-2050.f, 0.f, LAYER_FOREGROUND_2));
			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::dynamicCast<renderer::SpriteComponent>(rtti::RTTI::generateSerializable("SpriteComponent", instance->getContextData()));
			sprite->setTexture("trans.png");

			physics::Box2DRigidBodyComponent *phys = rtti::dynamicCast<physics::Box2DRigidBodyComponent>(rtti::RTTI::generateSerializable("Box2DRigidBodyComponent", instance->getContextData()));

			phys->setMass(5);
			phys->setFriction(1.f);
			phys->setDensity(1.0f);
			phys->setKinematic(true);
			//phys->setGroup(physics::BOX2D_GROUP_LEVEL);
			phys->setGroup(physics::BOX2D_GROUP_NONSOLID_OBJECT);

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);

			instance->getScene()->addEntity(entity);
		}

		LOG_INFO("Physics test scene loaded!");
	}

}
