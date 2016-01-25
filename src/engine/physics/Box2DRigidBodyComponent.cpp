// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/physics/Box2DRigidBodyComponent.h"
#include "engine/physics/Box2DPhysicSystem.h"
#include "engine/scene/TransformComponent.h"
#include "engine/renderer/TextureResource.h"
#include "engine/renderer/SpriteComponent.h"
#include "engine/scene/Entity.h"

#include "engine/stream/BufferedOutputStream.h"

#include <Box2D/Box2D.h>

namespace engine {
namespace physics {

	DECLARE_CLASS(Box2DRigidBodyComponent, engine::component::Component);

	BEGIN_PROPERTIES(Box2DRigidBodyComponent);
		DECLARE_PROPERTY(bool, Kinematic);
		DECLARE_PROPERTY(float, Mass);
		DECLARE_PROPERTY(float, Density); //TODO: update these from fly!
		DECLARE_PROPERTY(float, Friction);
		DECLARE_PROPERTY(float, Restitution);
		DECLARE_PROPERTY(int, BodyShape);
		DECLARE_PROPERTY(bool, FixedRotation);
		DECLARE_PROPERTY(float, GravityScale);
		DECLARE_PROPERTY(int, Group);
		DECLARE_PROPERTY(int, SizeX);
		DECLARE_PROPERTY(int, SizeY);
	END_PROPERTIES(Box2DRigidBodyComponent);

	BEGIN_DEPENDENCIES(Box2DRigidBodyComponent);
		REQUIRE_COMPONENT(TransformComponent);
	END_DEPENDENCIES

	Box2DRigidBodyComponent::Box2DRigidBodyComponent(void *context)
		: Component(context)
		, mass(1)
		, body(NULL)
		, kinematic(false)
		, density(1.f)
		, friction(0.f)
		, restitution(0.f)
		, onHitEvent(NULL)
		, bodyShape(SHAPE_BOX)
		, fixedRotation(false)
		, gravityScale(1.f)
		, nextTransformDirty(false)
		, nextAngleDirty(false)
		, group(BOX2D_GROUP_SOLID_OBJECT)
		, sizeX(0)
		, sizeY(0)
	{ }

	Box2DRigidBodyComponent::~Box2DRigidBodyComponent() 
	{ 
		if (onHitEvent != NULL)
			delete onHitEvent; 
	}

	void Box2DRigidBodyComponent::init()
	{
		PROFILE;
		//TODO: lot of values that should be possible to modify

		getBox2DPhysicSystem()->addComponent(this);

		scene::TransformComponent *transform = getParent()->findComponent<scene::TransformComponent>();

		math::Vec3 pos = transform->getPosition();

		// Search for the SpriteComponent, if it exists, find the scale from that.
		if (sizeX == 0 || sizeY == 0)
		{
			renderer::SpriteComponent *spriteComponent = getParent()->findComponent<renderer::SpriteComponent>();

			if (spriteComponent != NULL)
			{
				if (spriteComponent->getTextureResource() == NULL)
				{
					sizeX = 32;
					sizeY = 32;
				}
				else
				{
					sizeX = spriteComponent->getTextureResource()->getWidth();
					sizeY = spriteComponent->getTextureResource()->getHeight();
				}
			}
		}

		// Data for the b2 object
		b2FixtureDef fixtureDef;
		b2BodyDef bodyDef;

		// Setup all shapes, only use one of them! (TODO: perf test this)
		b2PolygonShape boxShape;
		b2CircleShape circleShape;

		boxShape.SetAsBox(float(sizeX) / Box2DPhysicSystem::getPhysicsWorldScale(), float(sizeY) / Box2DPhysicSystem::getPhysicsWorldScale() );
		circleShape.m_radius = float(sizeX) / Box2DPhysicSystem::getPhysicsWorldScale();
		circleShape.m_p = b2Vec2(0.f, 0.f);

		if (kinematic)
			bodyDef.type = b2_staticBody;
		else
			bodyDef.type = b2_dynamicBody;

//		bodyDef.position.Set(pos.x / (Box2DPhysicSystem::getPhysicsWorldScale() * sizeScale), pos.y / (Box2DPhysicSystem::getPhysicsWorldScale() * sizeScale));
		bodyDef.position.Set(pos.x / (Box2DPhysicSystem::getPhysicsWorldScale()), pos.y / (Box2DPhysicSystem::getPhysicsWorldScale()));

		bodyDef.angle = std::atan2(transform->getDirection().y, transform->getDirection().x);
		bodyDef.awake = true;

		body = getBox2DPhysicSystem()->getWorld()->CreateBody(&bodyDef);

		body->SetAngularDamping(0);
		body->SetLinearDamping(0);

		b2MassData massData;

		massData.mass = mass;
		massData.center = b2Vec2(0, 0);
		massData.I = 1; 

		body->ResetMassData();
		body->SetMassData(&massData);

		// choose right shape
		switch (bodyShape)
		{
		case SHAPE_BOX:
			fixtureDef.shape = &boxShape;
			break;
		case SHAPE_CIRCLE:
			fixtureDef.shape = &circleShape;
			break;
		default:
			LOG_ERROR("Invalid BodyShape for Box2DRigidBodyComponent!");
			break;
		}

		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;

		if (group == BOX2D_GROUP_NONSOLID_OBJECT)
			fixtureDef.isSensor = true;

		fixtureDef.filter.categoryBits = group;
		fixtureDef.filter.maskBits = 0xffff;

		body->CreateFixture(&fixtureDef);
		body->SetUserData(this);
		body->SetFixedRotation(fixedRotation);
		body->SetGravityScale(gravityScale);
	}

	void Box2DRigidBodyComponent::onHit(Box2DRigidBodyComponent *other)
	{
		if (onHitEvent == NULL)
			return;

		stream::BufferedOutputStream<stream::NativeEndian> params;
		params.write(other->getHandleId());

		onHitEvent->call(stream::InputStream<stream::NativeEndian>(params.getData()));
	}

	void Box2DRigidBodyComponent::onHitEnd(Box2DRigidBodyComponent *other) { }

	void Box2DRigidBodyComponent::clearOnHitEvent()
	{
		if (onHitEvent == NULL)
			return;

		delete onHitEvent;

		onHitEvent = NULL;
	}

	void Box2DRigidBodyComponent::uninit()
	{
		getBox2DPhysicSystem()->getWorld()->DestroyBody(body);
		getBox2DPhysicSystem()->removeComponent(this);
		onHitEvent = NULL;
	}

	void Box2DRigidBodyComponent::applyImpulse(const math::Vec2 impulse)
	{
		assert(body != NULL);

		body->ApplyLinearImpulse(b2Vec2(impulse.x, impulse.y), body->GetWorldCenter(), true);
	}

	void Box2DRigidBodyComponent::setVelocity(const math::Vec2 vel)
	{
		assert(body != NULL);

		body->SetLinearVelocity(b2Vec2(vel.x, vel.y));
	}

	void Box2DRigidBodyComponent::setAngularVelocity(const float angleVel)
	{
		assert(body != NULL);

		body->SetAngularVelocity(angleVel);
	}

	float Box2DRigidBodyComponent::getAngularVelocity()
	{
		assert(body != NULL);

		return body->GetAngularVelocity();
	}

	math::Vec2 Box2DRigidBodyComponent::getVelocity()
	{
		assert(body != NULL);

		const b2Vec2& vel = body->GetLinearVelocity();
		return math::Vec2(vel.x, vel.y);
	}

	void Box2DRigidBodyComponent::applyForce(const math::Vec2 force)
	{
		assert(body != NULL);
		body->ApplyForceToCenter(b2Vec2(force.x, force.y), true);
	}

	void Box2DRigidBodyComponent::setPosition(const math::Vec2 pos)
	{
		nextTransform = pos;
		nextTransformDirty = true;
	}

	void Box2DRigidBodyComponent::setAngle(const float angle)
	{
		nextAngleDirty = true;
		nextAngle = angle;
	}

	void Box2DRigidBodyComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void Box2DRigidBodyComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}
