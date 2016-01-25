// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PHYSICS_BOX2DPHYSICSYSTEM_H
#define ENGINE_PHYSICS_BOX2DPHYSICSYSTEM_H

#include "engine/SystemBase.h"
#include "engine/physics/BoxContactListener.h"

PROPELLER_FORWARD_DECLARE(b2World);
PROPELLER_FORWARD_DECLARE_2(engine, physics, Box2DRigidBodyComponent);
PROPELLER_FORWARD_DECLARE_2(engine, physics, Box2DCharacterComponent);

namespace engine {
namespace physics {

	class Box2DPhysicSystem : public engine::SystemBase
	{
	private:
		b2World *world;
		BoxContactListener contactListener;

	public:
		bool init();
		void uninit();
		void update(float delta);

		const String getName() { return "Box2DPhysicSystem"; }

		b2World *getWorld() { return world; }

		static const int getPhysicsWorldScale() { return 32; } // what size is equal to 1 in box2d world.

	private:
		void handleRigidBody(Box2DRigidBodyComponent *rigidBody);
		void handleCharacter(Box2DCharacterComponent *character);
	};

}
}

#endif