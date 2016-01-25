// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/physics/RigidBodyComponent.h"

#include "engine/stream/OutputStream.h"
#include "engine/stream/InputStream.h"
#include "engine/component/ComponentHolder.h"
#include "engine/stream/Serializable.h"
#include "engine/scene/TransformComponent.h"
#include "engine/math/Vector.h"
#include "engine/scene/Scene.h"

#include "engine/SystemBase.h"
#include "engine/physics/PhysicSystem.h"

#include <btBulletDynamicsCommon.h>

namespace engine {
namespace physics {

	DECLARE_CLASS(RigidBodyComponent, engine::component::Component);

	BEGIN_PROPERTIES(RigidBodyComponent);
		DECLARE_PROPERTY(Vec3, Velocity);
		DECLARE_PROPERTY(PropellerEnum, Shape);
		DECLARE_PROPERTY(float, Mass);
		DECLARE_PROPERTY(bool, StaticBody);
	END_PROPERTIES(RigidBodyComponent);

	BEGIN_DEPENDENCIES(RigidBodyComponent);
		REQUIRE_COMPONENT(TransformComponent);
	END_DEPENDENCIES;

	RigidBodyComponent::RigidBodyComponent(void *context)
		: Component(context)
		, velocity(math::Vec3(0, 0, 0))
		, motionState(NULL)
	{ }

	void RigidBodyComponent::init()
	{
		PROFILE;

		getPhysicSystem()->addComponent(this);

		scene::TransformComponent *transform = getParent()->findComponent<scene::TransformComponent>();

		collisionShape = new btSphereShape(1.f);

		math::Vec3 pos = transform->getPosition();

		motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));

		btVector3 localInertia(btScalar(0), btScalar(0), btScalar(0));
		collisionShape->calculateLocalInertia(mass, localInertia);

		btRigidBody::btRigidBodyConstructionInfo ci(mass, motionState, collisionShape, localInertia);

		rigidBody = new btRigidBody(ci);

		getPhysicSystem()->getDynamicsWorld()->addRigidBody(rigidBody);
	}

	void RigidBodyComponent::uninit()
	{
		LOG_INFO("physiccomp uninit");

		LOG_WARNING("Physic comp cleanup NOT DONE TODO");
	}

	RigidBodyComponent::~RigidBodyComponent()
	{
		if(isContextValid())
			getPhysicSystem()->removeComponent(this);

		if (motionState != NULL)
			delete motionState;

		LOG_WARNING("Cleanup missing for PhysicComponent!");
		// TODO: CLEANUP MISSING
	}

	void RigidBodyComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void RigidBodyComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}
