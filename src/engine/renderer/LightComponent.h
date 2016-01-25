// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#pragma once

#include "engine/component/Component.h"

namespace engine {
namespace renderer {

	class LightComponent : public engine::component::Component
	{
	public:
		DEFINE_COMPONENT(LightComponent);

		DEFINE_PROPERTY(math::Vec3, color, Color);
		DEFINE_PROPERTY(float, distance, Distance);

	public:
		LightComponent(void *context);
		~LightComponent();

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);
	};

}
}
