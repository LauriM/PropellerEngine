#pragma once

#include "engine/math/Vector.h"

#include "engine/component/Component.h"
#include "engine/stream/Serializable.h"
#include "engine/stream/OutputStream.h"

namespace engine {
namespace scene {

	class TransformComponent : public engine::component::Component
	{
	public:
		DEFINE_COMPONENT(TransformComponent);

		// Define the properties
		// first field defines type, second field defines the name of the property
		// for example the position is actually this->position, just a local variable.
		// the last field is the position in uppercase, this is used to have the getPosition(), setPosition() have the correct casing.
		// 
		// DO use the get/set versions if you want to ensure support for future features like networking (?)
		DEFINE_PROPERTY(math::Vec3, position, Position);
		DEFINE_PROPERTY(math::Vec3, direction, Direction);
		DEFINE_PROPERTY(float, scale, Scale);

	public:
		// constructor can still be used nicely to set the default values. This is important, because if you dont set defualt values, it can be anything.
		TransformComponent(void *context)
			: Component(context) // context is passed to the baseclass, important
			, position(math::Vec3(1, 1, 1))
			, direction(math::Vec3(1.0f, 1.0f, 1.0f))
			, scale(1.f)
		{ }

		// Save and load functionaltiy in the .cpp file
		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);

	};


}
}
