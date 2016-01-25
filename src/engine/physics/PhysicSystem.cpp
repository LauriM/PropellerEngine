// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/physics/PhysicSystem.h"
#include "engine/physics/RigidBodyComponent.h"
#include "engine/scene/TransformComponent.h"
#include "engine/scene/Entity.h"
#include "engine/physics/BulletDebugDraw.h"
#include "engine/console/Cvar.h"

#include <btBulletDynamicsCommon.h>

namespace cvar {
	CVAR(int, phys_debugdraw, 0, false);
}

namespace engine {
namespace physics {

	bool PhysicSystem::init()
	{
		PROFILE;

		LOG_INFO("PhysicSystem init!");

		broadphase = new btDbvtBroadphase();

		collisionConfiguration = new btDefaultCollisionConfiguration();
		dispatcher = new btCollisionDispatcher(collisionConfiguration);
		solver = new btSequentialImpulseConstraintSolver;
		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, -10, 0));

		groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

		groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));

		btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));

		groundBody = new btRigidBody(groundRigidBodyCI);

		dynamicsWorld->addRigidBody(groundBody);

#if defined (RENDERING_ENABLED)
		bulletDebugDraw = new BulletDebugDraw(debugDrawSystem);
		dynamicsWorld->setDebugDrawer(bulletDebugDraw);
#endif

		return true;
	}

	void PhysicSystem::uninit()
	{
		LOG_INFO("PhysicSystem uninit!");

		delete dynamicsWorld;
		delete solver;
		delete dispatcher;
		delete collisionConfiguration;
		delete broadphase;
	}

	void PhysicSystem::update(float delta)
	{
		PROFILE;

		int asdf = dynamicsWorld->getNumCollisionObjects();
		//TODO: make the timestep a cvar!
		dynamicsWorld->stepSimulation(1 / 60.f, 10);

#if defined (RENDERING_ENABLED)
		if (*cvar::phys_debugdraw)
			dynamicsWorld->debugDrawWorld();
#endif

		//TODO: Jobify this!
		float physScale = 13.f;

		// Sync the RigidBodies
		for (unsigned i = 0; i < components.size(); ++i)
		{
			RigidBodyComponent *rigidBody = dynamic_cast<RigidBodyComponent*>(components[i]);

			scene::TransformComponent *transform = rigidBody->getParent()->findComponent<scene::TransformComponent>();

			btTransform worldTransform;
			rigidBody->getMotionState()->getWorldTransform(worldTransform);

			btVector3 pos = worldTransform.getOrigin();
			btQuaternion quat = worldTransform.getRotation();
			btVector3 rot = quat.getAxis();

			math::Vec3 posPropeller(pos.getX(), pos.getY(), pos.getZ());

			posPropeller *= physScale;

			transform->setPosition(posPropeller);
			transform->setDirection(math::Vec3(rot.getX(), rot.getY(), rot.getZ()));
		}
	}

}
}
