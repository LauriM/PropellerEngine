// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_TRANSFORMCOMPONENT_H
#define ENGINE_SCENE_TRANSFORMCOMPONENT_H

#include "engine/math/Vector.h"

#include "engine/component/Component.h"
#include "engine/stream/Serializable.h"
#include "engine/stream/OutputStream.h"

namespace engine {
namespace scene {

	class TransformComponent : public engine::component::Component
	{
	public:
		DEFINE_CLASS(TransformComponent);

		GENERATE_STATIC_PROPERTY_VECTOR;

		DEFINE_PROPERTY_CUSTOM_GET(math::Vec3, position, Position);
		DEFINE_PROPERTY(math::Vec3, direction, Direction);
		DEFINE_PROPERTY(float, scale, Scale);

	public:
		TransformComponent(void *context)
			: Component(context)
			, position(math::Vec3(1, 1, 1))
			, direction(math::Vec3(1.0f, 1.0f, 1.0f))
			, scale(1.f)
		{ }

		// Applies parents position if its avaivable
		math::Vec3 getPosition();

		// If parented, returns the relative position, if not parented, returns the current position
		math::Vec3 getRelativePosition() { return position; }

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);
	};


}
}

#endif
