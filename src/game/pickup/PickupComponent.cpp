// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "game/pickup/PickupComponent.h"
#include "engine/physics/Box2DRigidBodyComponent.h"
#include "engine/scene/Entity.h"
#include "game/player/PlayerInputComponent.h"

namespace game {

	DECLARE_CLASS(PickupComponent, engine::component::Component);

	BEGIN_DEPENDENCIES(PickupComponent)
		REQUIRE_COMPONENT(Box2DRigidBodyComponent);
	END_DEPENDENCIES;

	PickupComponent::PickupComponent(void *context)
		: Component(context)
	{ }

	PickupComponent::~PickupComponent() { }

	void PickupComponent::init()
	{
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		rigidBody->setOnHitEvent(this, &PickupComponent::onHit);
	}

	void PickupComponent::uninit()
	{
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (rigidBody == NULL)
			return;

		rigidBody->clearOnHitEvent();
	}

	void PickupComponent::onHit(unsigned otherHandle)
	{
#ifndef DEDICATED_SERVER
		return; // Hits are disabled on client side
#endif
		engine::physics::Box2DRigidBodyComponent *rigidBody = engine::rtti::dynamicCast<engine::physics::Box2DRigidBodyComponent>(getHandleManager()->getHandle(otherHandle));

		player::PlayerInputComponent *player = rigidBody->getParent()->findComponent<player::PlayerInputComponent>();

		if (player != NULL)
		{
			LOG_INFO("HIT TO PLAYER!");
			//rigidBody->setPosition(math::Vec2(5000.f, 5000.f));
			getParent()->destroy();
		}
	}

}