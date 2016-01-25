// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "game/player/PlayerInputSystem.h"
#include "game/player/PlayerInputComponent.h"
#include "engine/component/ComponentHolder.h"
#include "engine/physics/Box2DCharacterComponent.h"
#include "engine/scene/TransformComponent.h"

namespace game {
namespace player {

	bool PlayerInputSystem::init()
	{
		return true;
	}

	void PlayerInputSystem::uninit() { }

	void PlayerInputSystem::update(float delta)
	{
		PROFILE;

		for (unsigned i = 0; i < components.size(); ++i)
		{
			PlayerInputComponent *inputComponent = rtti::dynamicCast<PlayerInputComponent>(components[i]);

			physics::Box2DCharacterComponent *rigidBody = inputComponent->getParent()->findComponent<physics::Box2DCharacterComponent>();

			const math::Vec2 &movement = inputComponent->getMovement();

			// Apply force
			/*
			math::Vec2 vel = rigidBody->getVelocity();

			float maxVel = 25.f;

			if (vel.x > maxVel)
				return;

			if (vel.x < -maxVel)
				return;

			rigidBody->applyForce(movement * 150);
			*/

			// Limit max speed

			//var speed : Number = body.m_linearVelocity.Normalize(); // sets vector length to 1, returns original length of vector
			//body.m_linearVelocity.Multiply(Math.min(speed, maxSpeed));
		}
	}

}
}