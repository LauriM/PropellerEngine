// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/math/Vector.h"
#include "engine/scene/CameraComponent.h"
#include "engine/component/ComponentHolder.h"
#include "engine/scene/TransformComponent.h"
#include "engine/renderer/CameraSystem.h"

namespace engine {
namespace scene {

	DECLARE_CLASS(CameraComponent, engine::component::Component);

	BEGIN_DEPENDENCIES(CameraComponent)
		REQUIRE_COMPONENT(TransformComponent);
	END_DEPENDENCIES;

	BEGIN_PROPERTIES(CameraComponent);
		DECLARE_PROPERTY(bool, Active);
	END_PROPERTIES(CameraComponent);

	CameraComponent::CameraComponent(void *context)
		: Component(context)
	{
		if (isContextValid())
			getCameraSystem()->addComponent(this);
	}

	CameraComponent::~CameraComponent()
	{
		if (isContextValid())
		{
			getCameraSystem()->setInactive(this);
			getCameraSystem()->removeComponent(this); //TODO: customize the removal and make sure it removes the active camera status if the same as removed component
		}
	}

	void CameraComponent::setActive(const bool &e)
	{
		active = e;

		if (active)
		{
			getCameraSystem()->setActive(this);

			// Inform the camera system that we are the active! (CameraSystem will reset the other cameras)
			getCameraSystem()->setCameraMode(renderer::CameraSystem::CAMERAMODE_COMPONENT);
		}

	}

	math::Vec3 CameraComponent::getCameraPosition()
	{
		TransformComponent *transform = this->getParent()->findComponent<TransformComponent>();
		return -transform->getPosition();
	}

	math::Vec3 CameraComponent::getCameraRotation()
	{
		TransformComponent *transform = this->getParent()->findComponent<TransformComponent>();
		return transform->getDirection();
	}

	void CameraComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void CameraComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}
