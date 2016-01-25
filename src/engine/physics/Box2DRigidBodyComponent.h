// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PHYSICS_BOX2DRIGIDBODYCOMPONENT_H
#define ENGINE_PHYSICS_BOX2DRIGIDBODYCOMPONENT_H

#include "engine/component/Component.h"

#include "engine/util/Bind.h"

PROPELLER_FORWARD_DECLARE(b2Body);

namespace engine {
namespace physics {

	enum Box2DRigidBodyShape {
		SHAPE_BOX = 0,
		SHAPE_CIRCLE,
	};

	enum Box2DEntityGroup {
		BOX2D_GROUP_LEVEL = 0x01,
		BOX2D_GROUP_SOLID_OBJECT = 0x02,
		BOX2D_GROUP_NONSOLID_OBJECT = 0x04
	};

	class Box2DRigidBodyComponent : public engine::component::Component
	{
	public:
		DEFINE_CLASS(Box2DRigidBodyComponent);

		GENERATE_STATIC_PROPERTY_VECTOR;

		GENERATE_COMPONENT_DEPENDENCY_LIST;

		DEFINE_PROPERTY(float, mass, Mass);
		DEFINE_PROPERTY(bool, kinematic, Kinematic);
		DEFINE_PROPERTY(float, density, Density);
		DEFINE_PROPERTY(float, restitution, Restitution);
		DEFINE_PROPERTY(float, friction, Friction);
		DEFINE_PROPERTY(int, bodyShape, BodyShape);
		DEFINE_PROPERTY(bool, fixedRotation, FixedRotation);
		DEFINE_PROPERTY(float, gravityScale, GravityScale);
		DEFINE_PROPERTY(int, group, Group); // Use the Box2DEntityGroup enum on this

		// Use sizeX/sizeY to define custom width, before adding the specific entity to the scene. Values are in pixels.
		// If the shape is circle, sizeX represents the radius
		DEFINE_PROPERTY(int, sizeX, SizeX);
		DEFINE_PROPERTY(int, sizeY, SizeY);

		//TODO: add restitution

		//NOTE: mass, friction, density, etc are not updated on fly! Ping engine dev if you need this

	private:
		b2Body *body;

		// Dirty flags etc to make sure setPosition can be called when inside a callback
		bool nextTransformDirty;
		bool nextAngleDirty;
		math::Vec2 nextTransform;
		float nextAngle;

		util::BindBase *onHitEvent;

	public:
		template <typename ClassT>
		void setOnHitEvent(ClassT *obj, void (ClassT::*func)(unsigned))
		{
			if (onHitEvent != NULL)
				delete onHitEvent; //delete old bind

			engine::util::Bind_1<ClassT, unsigned> *bind = new engine::util::Bind_1<ClassT, unsigned>();
			bind->obj = obj;
			bind->func = func;

			onHitEvent = bind;
		}

		void clearOnHitEvent();

		Box2DRigidBodyComponent(void *context);
		~Box2DRigidBodyComponent();

		void init();
		void uninit();

		// Event called by the engine, set your own event with setOnHitEvent
		void onHit(Box2DRigidBodyComponent *other);

		// NOTE: THIS CALL IS NOT YET IMPLEMENTED!
		void onHitEnd(Box2DRigidBodyComponent *other);

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);

		//! NOTE: Some calls are going to assert if the body is not created. Before initialization only set properties! 

		// Apply impulse to the this component
		void applyImpulse(const math::Vec2 impulse);

		// Apply force to this component
		void applyForce(const math::Vec2 force);

		// Set velocity for this component
		void setVelocity(const math::Vec2 vel);
		math::Vec2 getVelocity();

		// Set angle velocity
		void setAngularVelocity(const float angleVel);
		float getAngularVelocity();

		// Set position of the entity, transformComponent setPosition cannot be used, because the physicssystem would overwrite it
		void setPosition(const math::Vec2 pos);

		// Set angle, transformComponents direction cannot be used because the physicssystem would overwrite it
		void setAngle(const float pos);

		b2Body *getB2Body() { return body; }

		// engine related calls:
		bool isNextTransformDirty() { return nextTransformDirty; }
		bool isNextAngleDirty() { return nextAngleDirty; }

		const math::Vec2 getNextTransform() { return nextTransform; }
		const float getNextAngle() { return nextAngle; }

		void clearNextTransformDirtyFlags() { nextTransformDirty = false; nextAngleDirty = false; }
	};

}
}

#endif
