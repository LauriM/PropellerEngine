// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/SpriteComponent.h"
#include "engine/SystemBase.h"
#include "engine/resource/ResourceManager.h"
#include "engine/renderer/RendererSystem.h"

namespace engine {
namespace renderer {

	DECLARE_CLASS(SpriteComponent, engine::component::Component);

	BEGIN_PROPERTIES(SpriteComponent);
		DECLARE_PROPERTY(String, Texture);
		DECLARE_PROPERTY(bool, DrawEnabled);
		DECLARE_PROPERTY(bool, DrawToScreenCoordinates);
		DECLARE_PROPERTY(bool, DisableCullCheck);
		DECLARE_PROPERTY(float, WidthScale);
		DECLARE_PROPERTY(float, HeightScale);
	END_PROPERTIES(SpriteComponent);

	BEGIN_DEPENDENCIES(SpriteComponent);
		REQUIRE_COMPONENT(TransformComponent);
	END_DEPENDENCIES;

	SpriteComponent::SpriteComponent(void *context)
		: Component(context)
		, drawEnabled(true)
		, drawToScreenCoordinates(false)
		, disableCullCheck(false)
		, widthScale(1.f)
		, heightScale(1.f)
	{
#ifndef NULLRENDERER
		if (isContextValid())
			getRendererSystem()->addSpriteComponent(this);
#endif
	}

	SpriteComponent::~SpriteComponent()
	{
#ifndef NULLRENDERER
		if (isContextValid())
			getRendererSystem()->removeSpriteComponent(this);
#endif
	}

	void SpriteComponent::setTexture(const String &textureName)
	{
		texture = textureName;

		if (!isContextValid())
			return;

		// Texture has changed, reload
		reloadTexture();
	}

	void SpriteComponent::reloadTexture()
	{
		assert(texture != "");

		textureResource = (renderer::TextureResource*)getResourceManager()->getResourceByName(texture);
	}

	void SpriteComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void SpriteComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}
