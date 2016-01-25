// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_SPRITECOMPONENT_H
#define ENGINE_RENDERER_SPRITECOMPONENT_H

#include "engine/component/Component.h"
#include "engine/renderer/RendererBackend.h"
#include "engine/renderer/SpriteLayerDefinition.h"

PROPELLER_FORWARD_DECLARE_2(engine, renderer, TextureResource);

namespace engine {
namespace renderer {

	class SpriteComponent : public engine::component::Component
	{
	public:
		DEFINE_COMPONENT(SpriteComponent);

		DEFINE_PROPERTY_CUSTOM_SET(String, texture, Texture);
		DEFINE_PROPERTY(bool, drawEnabled, DrawEnabled);
		DEFINE_PROPERTY(bool, drawToScreenCoordinates, DrawToScreenCoordinates);
		DEFINE_PROPERTY(bool, disableCullCheck, DisableCullCheck);
		DEFINE_PROPERTY(float, widthScale, WidthScale);
		DEFINE_PROPERTY(float, heightScale, HeightScale);

	private:
		TextureResource *textureResource;

	public:
		SpriteComponent(void *context);
		~SpriteComponent();

		void setTexture(const String &textureName); 

		TextureResource *getTextureResource() const { return textureResource; }

		// reloads the texture to the GPU memory
		void reloadTexture();

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);
	};

}
}

#endif
