// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PHYSICS_BOX2DCHARACTERCOMPONENT_H
#define ENGINE_PHYSICS_BOX2DCHARACTERCOMPONENT_H

#include "engine/component/Component.h"

PROPELLER_FORWARD_DECLARE(b2Body);

// NOTE : THIS IS STILL WORK IN PROGRESS AND DOESN'T YET WORK AS EXPECTED!

namespace engine {
namespace physics {

	// 2D platformer character movement component
	// Creates box2d object with two shapes, handles jumping and hit detection
	// Provides hit events for the game components
	class Box2DCharacterComponent : public engine::component::Component
	{
	public:
		DEFINE_CLASS(Box2DCharacterComponent);

		GENERATE_STATIC_PROPERTY_VECTOR;

		GENERATE_COMPONENT_DEPENDENCY_LIST;

		DEFINE_PROPERTY(int, sizeScale, SizeScale);

	private:
		b2Body *body;

	public:

		Box2DCharacterComponent(void *context);
		~Box2DCharacterComponent();

		void init();
		void uninit();

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);

		void jump();

		b2Body *getB2Body() { return body; }
	};

}
}

#endif
