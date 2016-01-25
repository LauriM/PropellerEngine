// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/physics/Box2DPhysicSystem.h"
#include "engine/physics/Box2DRigidBodyComponent.h"
#include "engine/physics/Box2DCharacterComponent.h"
#include "engine/scene/Entity.h"
#include "engine/scene/TransformComponent.h"

#include "engine/sys/Scheduler.h"

#include <Box2D/Box2D.h>

namespace engine {
namespace physics {

	bool Box2DPhysicSystem::init()
	{
		PROFILE;

		b2Vec2 gravity(0.0f, -10.f);

		world = new b2World(gravity);
		world->SetContactListener(&contactListener);

		return true;
	}

	void Box2DPhysicSystem::uninit()
	{
		delete world;
	}

	void handleRigidBodyJob(void *userdata)
	{
		PROFILE;
		Box2DRigidBodyComponent *comp = rtti::dynamicCast<Box2DRigidBodyComponent>((component::Component*)userdata);

		// NOT A RIGID BODY!
		if (comp == NULL)
			return;

		//TODO: Some optimization could be used over here in the synchronization
		bool locationChange = false;

		// Check if there is a transform operations in queue
		if (comp->isNextTransformDirty())
		{
			comp->getB2Body()->SetTransform(b2Vec2(comp->getNextTransform().x / (Box2DPhysicSystem::getPhysicsWorldScale()), comp->getNextTransform().y / (Box2DPhysicSystem::getPhysicsWorldScale())), comp->getB2Body()->GetAngle());
			locationChange = true;
		}

		if (comp->isNextAngleDirty())
		{
			comp->getB2Body()->SetTransform(comp->getB2Body()->GetTransform().p, comp->getNextAngle());
			locationChange = true;
		}

		comp->clearNextTransformDirtyFlags();

		if (!comp->getKinematic() || locationChange)
		{
			scene::TransformComponent *transform = comp->getParent()->findComponent<scene::TransformComponent>();

			// Update the position back to transformcomponent
			math::Vec3 p = math::Vec2(comp->getB2Body()->GetPosition().x * Box2DPhysicSystem::getPhysicsWorldScale(), comp->getB2Body()->GetPosition().y * Box2DPhysicSystem::getPhysicsWorldScale());
			p.z = transform->getPosition().z; // Preventing z to be changed to 0 !

			// NETWORK OPTIMIZATION, don't set if it doesn't change the value
			if (transform->getPosition() != p)
				transform->setPosition(p);

			float angle = comp->getB2Body()->GetAngle();

			math::Vec3 d = math::Vec2(sin(angle), cos(angle));

			// NETWORK OPTIMIZATION, don't set if it doesn't change the value
			if (transform->getDirection() != d)
				transform->setDirection(d);
		}
	}

	void Box2DPhysicSystem::update(float delta)
	{
		PROFILE;

		world->Step(delta, 6, 2);

		// Single Thread
		for (unsigned i = 0; i < components.size(); ++i)
			handleRigidBodyJob(components[i]);

		// TODO: ULTIMATE FUCKING HACK ! Just hoping it works this way
		for (unsigned i = 0; i < components.size(); ++i)
		{
			Box2DCharacterComponent *c = rtti::dynamicCast<Box2DCharacterComponent>(components[i]);

			if (c != NULL)
				handleCharacter(c);
		}

		// Multithreading is temporary disabled because of the limit on the objects

		/*
		// Multithread
		if (components.size() == 0)
			return;

		sys::Scheduler *scheduler = components[0]->getContextData()->scheduler;
		sys::JobDecl jobs[1000];

		volatile unsigned counter = components.size();

		for (unsigned i = 0; i < components.size(); ++i)
		{
			jobs[i] = scheduler->declareJob(&handleRigidBodyJob, &counter, components[i]);
		}

		scheduler->runJobs(&jobs[0], components.size());

		// Wait for counter
		while (counter > 0) { }
		*/
	}

	void Box2DPhysicSystem::handleCharacter(Box2DCharacterComponent *comp)
	{
		scene::TransformComponent *transform = comp->getParent()->findComponent<scene::TransformComponent>();

		transform->setPosition(math::Vec2(comp->getB2Body()->GetPosition().x * (Box2DPhysicSystem::getPhysicsWorldScale() * comp->getSizeScale()), comp->getB2Body()->GetPosition().y * (Box2DPhysicSystem::getPhysicsWorldScale() * comp->getSizeScale())));
	}

}
}
