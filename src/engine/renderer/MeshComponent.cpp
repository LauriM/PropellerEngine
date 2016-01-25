// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/MeshComponent.h"
#include "engine/SystemBase.h"
#include "engine/renderer/ModelResource.h"
#include "engine/renderer/RendererSystem.h"
#include "engine/resource/ResourceManager.h"

namespace engine {
namespace renderer {

	DECLARE_CLASS(MeshComponent, engine::component::Component);

	BEGIN_DEPENDENCIES(MeshComponent);
		REQUIRE_COMPONENT(TransformComponent);
	END_DEPENDENCIES;

	BEGIN_PROPERTIES(MeshComponent);
		DECLARE_PROPERTY(String, ModelName);
		DECLARE_PROPERTY(String, Diffuse);
		DECLARE_PROPERTY(String, Normal);
		DECLARE_PROPERTY(String, Specular);
		DECLARE_PROPERTY(bool, Wireframe);
		DECLARE_PROPERTY(float, TextureScale);
	END_PROPERTIES(MeshComponent);

	MeshComponent::MeshComponent(void *context)
		: Component(context)
		, wireframe(false)
		, textureScale(1.f)
	{
#ifndef NULLRENDERER
		if (isContextValid())
			getRendererSystem()->addComponent(this);
#endif
	}

	MeshComponent::~MeshComponent()
	{
#ifndef NULLRENDERER
		if (isContextValid())
			getRendererSystem()->removeComponent(this);
#endif
	}

	void MeshComponent::setModelName(const String name)
	{
		modelName = name;

		modelResource = (engine::renderer::ModelResource*)getResourceManager()->getResourceByName(name);
	}

	void MeshComponent::setDiffuse(const String diffuseMap)
	{
		diffuse = diffuseMap;

		diffuseResource = (renderer::TextureResource*)getResourceManager()->getResourceByName(diffuseMap);
	}

	void MeshComponent::setNormal(const String normalMap)
	{
		normal = normalMap;

		normalResource = (renderer::TextureResource*)getResourceManager()->getResourceByName(normal);
	}

	void MeshComponent::setSpecular(const String specularMap)
	{
		specular = specularMap;

		specularResource = (renderer::TextureResource*)getResourceManager()->getResourceByName(specularMap);
	}

	void MeshComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void MeshComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}
