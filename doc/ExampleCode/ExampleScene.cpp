// Remember to always include the "game/precompiled.h", it provides important engine related stuff!
#include "game/precompiled.h"

// Include the header for the scene
#include "game/ExampleScene.h"

#include "engine/GameInstance.h"
#include "engine/scene/Entity.h"
#include "engine/scene/TransformComponent.h"
#include "engine/physics/Box2DRigidBodyComponent.h"
#include "game/player/PlayerInputComponent.h"
#include "engine/scene/CameraComponent.h"
#include "engine/renderer/SpriteComponent.h"
#include "engine/renderer/LightComponent.h"

// only use the namespaces in .cpp files, adding them to headers will mess up things
using namespace engine;
using namespace engine::scene;

namespace game {

	// instance provides access to the engine when the load is happening, all the changes should be loaded against it.
	void PhysicsTestScene::onSceneLoad(GameInstance *instance)
	{
		// Scopes are here just to make it easier to use the same name multiple times (entity, etc)
		{
			// creating a static ground with box2d physics
			Entity *entity = rtti::generate<Entity>(instance->getContextData());
			entity->setName("Ground");

			TransformComponent *transform = rtti::generate<TransformComponent>(instance->getContextData());

			// set position of the ground
			transform->setPosition(math::Vec3(50.f, 550.f, 0.f));
			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			// Create spritecomponent to display the image
			renderer::SpriteComponent *sprite = rtti::generate<renderer::SpriteComponent>(instance->getContextData());
			sprite->setTexture("hellknight.png"); // hellknight.png is automatically loaded and cached by the RendererSystem, etc on the background, no need to worry about it

			// Lets add 2D-physics
			physics::Box2DRigidBodyComponent *phys = rtti::generate<physics::Box2DRigidBodyComponent>(instance->getContextData());

			phys->setFriction(1.f);
			phys->setMass(5);
			phys->setDensity(1.0f);
			phys->setKinematic(true); // kinematic makes the object static. (useful for ground, etc)

			// Lets add all the components to the entity
			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);

			// aaand lets add the entity to the scene!
			instance->getScene()->addEntity(entity);
		}

		// And the lets create the player,
		{
			Entity *entity = rtti::generate<Entity>(instance->getContextData());
			entity->setName("Player"); // name can be checked  during the code, but string comparison is slow, so I would recommend to check against something else
			// for example if only the player has "PlayerInfoComponent" or something like that, you can try to find that component to 
			// detect the player.

			TransformComponent *transform = rtti::generate<TransformComponent>(instance->getContextData());

			transform->setPosition(math::Vec3(50.f, 750.f, 0.2f));
			transform->setDirection(math::Vec3(0.f, 0.f, 1.f));
			transform->setScale(1.f);

			renderer::SpriteComponent *sprite = rtti::generate<renderer::SpriteComponent>(instance->getContextData());
			sprite->setTexture("testcube.png");

			physics::Box2DRigidBodyComponent *phys = rtti::generate<physics::Box2DRigidBodyComponent>(instance->getContextData());

			phys->setMass(5);
			phys->setFriction(1.f);
			phys->setDensity(1.0f);
			phys->setKinematic(false);

			player::PlayerInputComponent *playerInput = rtti::generate<player::PlayerInputComponent>(instance->getContextData());

			// camera is used to center the camera to the player
			scene::CameraComponent *camera = rtti::generate<scene::CameraComponent>(instance->getContextData());

			renderer::LightComponent *light = rtti::generate<renderer::LightComponent>(instance->getContextData());
			light->setColor(math::Vec3(0.8f, 0.8f, 1.f));

			entity->addComponent(transform);
			entity->addComponent(sprite);
			entity->addComponent(phys);
			entity->addComponent(playerInput);
			entity->addComponent(light);
			entity->addComponent(camera);

			instance->getScene()->addEntity(entity);

			camera->setActive(true);
		}

		LOG_INFO("Physics test scene loaded!");
	}

}
