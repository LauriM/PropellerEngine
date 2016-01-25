// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_COMPONENTTYPE_H
#define ENGINE_SCENE_COMPONENTTYPE_H

#include "engine/properties/Properties.h"

namespace engine {
namespace scene {

	union Value
	{
		unsigned valueUnsigned;
		signed valueSigned;
		bool valueBool;
		float valueFloat;
		double valueDouble;
	};

	struct PropertyType
	{
	public:
		String name;

		properties::PropertyType type;

		Value value;
		String valueString;
		math::Vec2 valueVec2;
	};

	typedef std::vector<PropertyType> PropertyTypeVector;

	class ComponentType
	{
	private:
		String name;

		PropertyTypeVector propertyTypeVector;
	public:
		ComponentType()
			: name("nil")
		{ }

		ComponentType(const String &name)
			: name(name)
		{ }

		const String &getName() const { return name; }
		void setName(String n) { name = n; }

		const PropertyTypeVector &getPropertyTypeVector() const { return propertyTypeVector; }
		PropertyTypeVector *getPropertyTypeVectorPtr() { return &propertyTypeVector; }
	};

}
}

#endif