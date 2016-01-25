// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PHYSICS_RIGIDBODYCOMPONENT_H
#define ENGINE_PHYSICS_RIGIDBODYCOMPONENT_H

#include "engine/component/Component.h"

#include "engine/stream/Serializable.h"

PROPELLER_FORWARD_DECLARE_2(engine, scene, Scene2D);
PROPELLER_FORWARD_DECLARE_2(engine, scene, PhysicSystem);
PROPELLER_FORWARD_DECLARE_1(engine, SystemBase);

PROPELLER_FORWARD_DECLARE_STRUCT(btDefaultMotionState);
PROPELLER_FORWARD_DECLARE(btCollisionShape);
PROPELLER_FORWARD_DECLARE(btRigidBody);

namespace engine {
namespace physics {

	enum CollisionShape
	{
		COLLISION_SHAPE_BOX = 0,
		COLLISION_SHAPE_SPREHE,
	};

	class RigidBodyComponent : public engine::component::Component
	{
	public:
		DEFINE_CLASS(RigidBodyComponent);

		GENERATE_STATIC_PROPERTY_VECTOR;
		
		GENERATE_COMPONENT_DEPENDENCY_LIST;

		DEFINE_PROPERTY(math::Vec3, velocity, Velocity);
		DEFINE_PROPERTY(PropellerEnum, Shape, Shape);
		DEFINE_PROPERTY(float, mass, Mass);
		DEFINE_PROPERTY(bool, staticBody, StaticBody);

	private:
		btDefaultMotionState *motionState;
		btCollisionShape *collisionShape;
		btRigidBody *rigidBody;

	public:
		RigidBodyComponent(void *context);
		~RigidBodyComponent();

		void init();
		void uninit();

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);

		btDefaultMotionState *getMotionState() { return motionState; }
	};

}
}

#endif