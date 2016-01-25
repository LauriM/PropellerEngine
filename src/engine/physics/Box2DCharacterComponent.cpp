// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/physics/Box2DCharacterComponent.h"
#include "engine/physics/Box2DPhysicSystem.h"
#include "engine/component/ComponentHolder.h"
#include "engine/scene/TransformComponent.h"

namespace engine {
namespace physics {
	DECLARE_CLASS(Box2DCharacterComponent, engine::component::Component);

	BEGIN_PROPERTIES(Box2DCharacterComponent);
		DECLARE_PROPERTY(int, SizeScale);
	END_PROPERTIES(Box2DCharacterComponent);

	BEGIN_DEPENDENCIES(Box2DCharacterComponent);
		REQUIRE_COMPONENT(TransformComponent);
	END_DEPENDENCIES

	Box2DCharacterComponent::Box2DCharacterComponent(void *context)
		: Component(context)
	{ }

	Box2DCharacterComponent::~Box2DCharacterComponent() { }

	void Box2DCharacterComponent::init()
	{
		PROFILE;

		getBox2DPhysicSystem()->addComponent(this);

		scene::TransformComponent *transform = getParent()->findComponent<scene::TransformComponent>();
		math::Vec3 pos = transform->getPosition();

		// Search for the SpriteComponent, if it exists, find the scale from that.
		sizeScale = 1; // default to 1, if sprite component doesn't exists
		/*
		renderer::SpriteComponent *spriteComponent = getParent()->findComponent<renderer::SpriteComponent>();

		if (spriteComponent != NULL)
		{
#ifndef NULLRENDERER
			unsigned width = spriteComponent->getTextureResource()->getWidth();
#else
			unsigned width = 32;
			LOG_WARNING("Linux version doesn't know how to load textures, reseting size!");
#endif

			//TODO: Fetch transform scale to this!
			sizeScale = width / Box2DPhysicSystem::getPhysicsWorldScale();
		}
		*/

		b2BodyDef bodyDef;

		bodyDef.type = b2_dynamicBody;

		bodyDef.position.Set(pos.x / (Box2DPhysicSystem::getPhysicsWorldScale()), pos.y / (Box2DPhysicSystem::getPhysicsWorldScale()));

		body = getBox2DPhysicSystem()->getWorld()->CreateBody(&bodyDef);

		body->SetAngularDamping(0);
		body->SetLinearDamping(0);

		b2MassData massData;
		massData.mass = 10;
		massData.center = b2Vec2(0, 0);
		massData.I = 1;

		body->SetMassData(&massData);

		// * Setup the fixtures *

		b2PolygonShape boxShape;
		b2CircleShape circleShape;

		boxShape.SetAsBox(float(sizeScale) / 2, float(sizeScale));

		circleShape.m_radius = float(sizeScale / 2);
		circleShape.m_p = b2Vec2(0, -float(sizeScale) / 2);

		{ // Circle fixture (feet)
			b2FixtureDef fixture;

			fixture.density = 1.f;
			fixture.friction = 0.8f;
			fixture.restitution = 0.0f;

			fixture.shape = &circleShape;

			body->CreateFixture(&fixture);
		}

		body->SetUserData(this);
		body->SetFixedRotation(true); //TODO: move to properties
		body->SetGravityScale(2); //TODO: move to properties
	}

	void Box2DCharacterComponent::jump()
	{
		body->ApplyForceToCenter(b2Vec2(0, 50), true);
	}

	void Box2DCharacterComponent::uninit()
	{
		getBox2DPhysicSystem()->getWorld()->DestroyBody(body);
		getBox2DPhysicSystem()->removeComponent(this);
	}

	void Box2DCharacterComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{

	}

	void Box2DCharacterComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{

	}

}
}
