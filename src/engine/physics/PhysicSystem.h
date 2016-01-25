// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PHYSICS_PHYSICSYSTEM_H
#define ENGINE_PHYSICS_PHYSICSYSTEM_H

#include "engine/SystemBase.h"

PROPELLER_FORWARD_DECLARE_2(engine, scene, PhysicComponent);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, DebugDrawSystem);
PROPELLER_FORWARD_DECLARE_2(engine, physics, BulletDebugDraw);

PROPELLER_FORWARD_DECLARE(btBroadphaseInterface);
PROPELLER_FORWARD_DECLARE(btDefaultCollisionConfiguration);
PROPELLER_FORWARD_DECLARE(btCollisionDispatcher);
PROPELLER_FORWARD_DECLARE(btSequentialImpulseConstraintSolver);
PROPELLER_FORWARD_DECLARE(btDiscreteDynamicsWorld);

PROPELLER_FORWARD_DECLARE(btCollisionShape);
PROPELLER_FORWARD_DECLARE_STRUCT(btDefaultMotionState);
PROPELLER_FORWARD_DECLARE(btRigidBody);

namespace engine {
namespace physics {

	class PhysicSystem : public engine::SystemBase
	{
	private:
		btBroadphaseInterface *broadphase;
		btDefaultCollisionConfiguration *collisionConfiguration;
		btCollisionDispatcher *dispatcher;
		btSequentialImpulseConstraintSolver *solver;
		btDiscreteDynamicsWorld *dynamicsWorld; 

		btCollisionShape *groundShape;
		btDefaultMotionState *groundMotionState;
		btRigidBody *groundBody;

		renderer::DebugDrawSystem *debugDrawSystem;
		BulletDebugDraw *bulletDebugDraw;

	public:
		PhysicSystem(renderer::DebugDrawSystem *debugDrawSystem)
			: debugDrawSystem(debugDrawSystem)
		{ }

		bool init();
		void uninit();
		void update(float delta);

		const String getName() { return "PhysicSystem"; }

		btDiscreteDynamicsWorld *getDynamicsWorld() { return dynamicsWorld; }
	};

}
}

#endif