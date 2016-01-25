// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/renderer/CameraSystem.h"
#include "engine/math/Vector.h"
#include "engine/math/Matrix.h"
#include "engine/GameInstance.h"
#include "engine/scene/CameraComponent.h"
#include "engine/console/Cvar.h"
#include <boost/lexical_cast.hpp>

namespace cvar {
	EXTERN_CVAR(int, dimensions);
}

namespace command {

	CREATE_COMMAND(getpos, "Get camera position")
	{
		engine::math::Vec3 pos = instance->getCameraSystem()->getPosition();
		engine::math::Quat rot = instance->getCameraSystem()->getRotation();

		LOG_INFO("setpos " << pos.x << " " << pos.y << " " << pos.z);

		return 0;
	}

	CREATE_COMMAND(setpos, "Set camera position")
	{
		engine::math::Vec3 position;

		if (args->size() < 4)
		{
			LOG_WARNING("Not enough parameters for setpos!");
			return -1;
		}

		position.x = boost::lexical_cast<float>(args->at(1));
		position.y = boost::lexical_cast<float>(args->at(2));
		position.z = boost::lexical_cast<float>(args->at(3));

		instance->getCameraSystem()->setPosition(position);

		return 0;
	}

}

namespace engine {
namespace renderer {

	CameraSystem::CameraSystem(engine::input::InputSystem *inputSystem)
		: position(math::Vec3(-10.f, 0.f, -10.f))
		, rotation(math::Quat())
		, mode(CAMERAMODE_COMPONENT)
		, up(math::Vec3(0.f, 1.f, 0.f))
		, inputSystem(inputSystem)
		, cameraMovement(math::Vec3i(0, 0, 0))
	{ }

	bool CameraSystem::init()
	{
		LOG_INFO("Enabling debugging freefly camera for development purposes!");

		mode = CAMERAMODE_DEBUG_FREEFLY;

		inputSystem->bindKeyEvent("cameraForward", this, &CameraSystem::forward);
		inputSystem->bindKeyEvent("cameraBack", this, &CameraSystem::back);
		inputSystem->bindKeyEvent("cameraRight", this, &CameraSystem::right);
		inputSystem->bindKeyEvent("cameraLeft", this, &CameraSystem::left);
			
		inputSystem->bindAxisEvent("cameraRotate", this, &CameraSystem::rotate);
		return true;
	}

	void CameraSystem::update(float delta)
	{
		if (mode == CAMERAMODE_DEBUG_FREEFLY)
		{
			if (*cvar::dimensions == 3)
			{
				// movement if enabled
				float speed = 1.5f;
				math::Vec3 movement;

				if (cameraMovement.z != 0)
				{
					movement.z = speed * cameraMovement.z;
				}

				if (cameraMovement.x != 0)
				{
					movement.x = speed * cameraMovement.x;
				}

				movement = rotation.rotateVector(movement);

				position -= movement;
			}

			if (*cvar::dimensions == 2)
			{
				position.x -= cameraMovement.x * 30;
				position.y -= cameraMovement.z * 30;
			}

			// Update the matrix
			cameraMatrix = math::Matrix4x4::getTranslation(position) * rotation.getMatrix();
		}

		if (mode == CAMERAMODE_COMPONENT)
		{
			if (activeCameraComponent == NULL)
			{
				mode = CAMERAMODE_DEBUG_FREEFLY;

				LOG_WARNING("[CameraSystem] Camera lost! Switching to freefly!");
				return;
			}

			position = activeCameraComponent->getCameraPosition();

			cameraMatrix = math::Matrix4x4::getTranslation(position);
		}
	}

	void CameraSystem::setActive(scene::CameraComponent *cameraComponent)
	{
		activeCameraComponent = cameraComponent;

		for (unsigned i = 0; i < components.size(); ++i)
		{
			scene::CameraComponent *cam = rtti::dynamicCast<scene::CameraComponent>(components[i]);

			if (cam != cameraComponent)
				cam->setActive(false); 
		}

		mode = CAMERAMODE_COMPONENT;
	}

	void CameraSystem::setInactive(scene::CameraComponent *cameraComponent)
	{
		if (activeCameraComponent == cameraComponent)
			activeCameraComponent = NULL;
	}

	scene::CameraComponent *CameraSystem::getActiveCameraComponent()
	{
		return activeCameraComponent;
	}

	void CameraSystem::rotate(const float x, const float y)
	{
		float sensitivity = 350.f;
		rotation = rotation * math::Quat(math::PI * -x * sensitivity, math::PI * -y* sensitivity, 0.f);;
	}

	const math::Matrix4x4 &CameraSystem::getMatrix() const
	{
		return cameraMatrix;
	}

	void CameraSystem::forward(bool isKeyDown)
	{
		if (isKeyDown)
			cameraMovement.z = 1;
		else
			cameraMovement.z = 0;
	}

	void CameraSystem::back(bool isKeyDown)
	{
		if (isKeyDown)
			cameraMovement.z = -1;
		else
			cameraMovement.z = 0;
	}

	void CameraSystem::right(bool isKeyDown)
	{
		if (isKeyDown)
			cameraMovement.x = 1;
		else
			cameraMovement.x = 0;
	}

	void CameraSystem::left(bool isKeyDown)
	{
		if (isKeyDown)
			cameraMovement.x = -1;
		else
			cameraMovement.x = 0;
	}

}
}