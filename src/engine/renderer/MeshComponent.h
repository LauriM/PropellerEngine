// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_MESHCOMPONENT_H
#define ENGINE_RENDERER_MESHCOMPONENT_H

#include "engine/component/Component.h"

PROPELLER_FORWARD_DECLARE_2(engine, renderer, SceneRendererSystem);
PROPELLER_FORWARD_DECLARE_1(engine, SystemBase);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, ModelResource);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, TextureResource);

namespace engine {
namespace renderer {

	class MeshComponent : public engine::component::Component
	{
	public:
		DEFINE_COMPONENT(MeshComponent);

		DEFINE_PROPERTY_CUSTOM_SET(String, modelName, ModelName); 
		DEFINE_PROPERTY_CUSTOM_SET(String, diffuse, Diffuse);
		DEFINE_PROPERTY_CUSTOM_SET(String, normal, Normal);
		DEFINE_PROPERTY_CUSTOM_SET(String, specular, Specular);
		DEFINE_PROPERTY(bool, wireframe, Wireframe);
		DEFINE_PROPERTY(float, textureScale, TextureScale);

	private:
		ModelResource *modelResource;

		TextureResource *diffuseResource;
		TextureResource *normalResource;
		TextureResource *specularResource;

	public:
		MeshComponent(void *context);
		~MeshComponent();

		void setModelName(const String name);
		void setDiffuse(const String diffuseMap);
		void setNormal(const String normalMap);
		void setSpecular(const String specularMap);

		const ModelResource *getModelResource() const { return modelResource; }
		TextureResource *getDiffuseResource() const { return diffuseResource; }
		TextureResource *getNormalResource() const { return normalResource; }
		TextureResource *getSpecularResource() const { return specularResource; }

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);
	};

}
}

#endif