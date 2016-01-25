// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "engine/component/ComponentHolder.h"
#include "game/player/PlayerInputComponent.h"
#include "engine/input/InputSystem.h"
#include "engine/physics/Box2DRigidBodyComponent.h"
#include "engine/console/Cvar.h"
#include "game/GameContext.h"
#include "engine/physics/Box2DCharacterComponent.h"
#include "game/player/PlayerInputSystem.h"

namespace cvar {
	EXTERN_CVAR(int, r_width);
	EXTERN_CVAR(int, r_height);
}

namespace game {
namespace player {

	DECLARE_CLASS(PlayerInputComponent, engine::component::Component);

	BEGIN_DEPENDENCIES(PlayerInputComponent)
		REQUIRE_COMPONENT(TransformComponent);
		REQUIRE_COMPONENT(Box2DRigidBodyComponent);
	END_DEPENDENCIES;

	PlayerInputComponent::PlayerInputComponent(void *context)
		: Component(context)
		, movement(math::Vec2(0.f, 0.f))
	{
		if (!isContextValid())
			return;

		getGameContext()->playerInputSystem->addComponent(this);

		getInputSystem()->bindAxisEvent("playermovement", this, &PlayerInputComponent::move);
		getInputSystem()->bindKeyEvent("playerup", this, &PlayerInputComponent::moveUp);
		getInputSystem()->bindKeyEvent("playerdown", this, &PlayerInputComponent::moveDown);
		getInputSystem()->bindKeyEvent("playerleft", this, &PlayerInputComponent::moveLeft);
		getInputSystem()->bindKeyEvent("playerright", this, &PlayerInputComponent::moveRight);
		getInputSystem()->bindKeyEvent("playerTouch", this, &PlayerInputComponent::playerTouch);
	}

	PlayerInputComponent::~PlayerInputComponent()
	{
		if (!isContextValid())
			return;

		getGameContext()->playerInputSystem->removeComponent(this);

		LOG_INFO("unbinding player input NOT IMPLEMENTED!");
	}

	void PlayerInputComponent::move(float x, float y)
	{
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (rigidBody == NULL)
			return;

//		rigidBody->applyImpulse(math::Vec2(x, -10));
		LOG_INFO("pos: " << x << "," << y);
	}

	void PlayerInputComponent::moveUp(bool k) 
	{ 
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (k)
			rigidBody->applyImpulse(math::Vec2(0, 70));
	} 

	void PlayerInputComponent::moveDown(bool k) 
	{ 
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (k)
			rigidBody->applyImpulse(math::Vec2(0, -70));
	}

	void PlayerInputComponent::moveLeft(bool k)
	{
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (k)
			rigidBody->applyImpulse(math::Vec2(-70, 0));
	}

	void PlayerInputComponent::moveRight(bool k)
	{
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (k)
			rigidBody->applyImpulse(math::Vec2(70, 0));
	}

	void PlayerInputComponent::playerTouch(bool v)
	{
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		const math::Vec2 &cursorPos = getInputSystem()->getCursorPosition();

		math::Vec2 impulse;

		if (cursorPos.x < (*cvar::r_width / 2))
			impulse.x = -100;
		else
			impulse.x = 100;

		if (cursorPos.y < (*cvar::r_height / 2))
			impulse.y = 100;
		else
			impulse.y = -100;

		if (v)
			rigidBody->applyImpulse(impulse);
	}

}
}

