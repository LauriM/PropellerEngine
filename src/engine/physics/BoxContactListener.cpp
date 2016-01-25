// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/physics/BoxContactListener.h"
#include "engine/physics/Box2DRigidBodyComponent.h"

namespace engine {
namespace physics {

	void BoxContactListener::BeginContact(b2Contact* contact)
	{
		PROFILE;

		Box2DRigidBodyComponent *bodyA = rtti::dynamicCast<Box2DRigidBodyComponent>((rtti::Object*)contact->GetFixtureA()->GetBody()->GetUserData());
		Box2DRigidBodyComponent *bodyB = rtti::dynamicCast<Box2DRigidBodyComponent>((rtti::Object*)contact->GetFixtureB()->GetBody()->GetUserData());

		if (bodyA == NULL || bodyB == NULL)
			return;

		bodyA->onHit(bodyB);
		bodyB->onHit(bodyA);

		//TODO: handle collisions of box2dcharacters
	}

	void BoxContactListener::EndContact(b2Contact* contact)
	{

	}

}
}