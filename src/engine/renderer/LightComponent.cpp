// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/LightComponent.h"
#include "engine/SystemBase.h"
#include "engine/renderer/RendererSystem.h"

namespace engine {
namespace renderer {

	DECLARE_CLASS(LightComponent, engine::component::Component);

	BEGIN_PROPERTIES(LightComponent);
		DECLARE_PROPERTY(Vec3, Color);
		DECLARE_PROPERTY(float, Distance);
	END_PROPERTIES(LightComponent);

	BEGIN_DEPENDENCIES(LightComponent);
		REQUIRE_COMPONENT(TransformComponent);
	END_DEPENDENCIES;

	LightComponent::LightComponent(void *context)
		: Component(context)
		, color(math::Vec3(1.f, 1.f, 1.f))
		, distance(100.f)
	{
#ifndef NULLRENDERER
		if (isContextValid())
			getRendererSystem()->addLightComponent(this);
#endif
	}

	LightComponent::~LightComponent()
	{
#ifndef NULLRENDERER
		if (isContextValid())
			getRendererSystem()->removeLightComponent(this);
#endif
	}

	void LightComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void LightComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}