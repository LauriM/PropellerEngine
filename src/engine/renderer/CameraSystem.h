// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_RENDERER_CAMERASYSTEM_H
#define ENGINE_RENDERER_CAMERASYSTEM_H

#include "engine/SystemBase.h"

#include "engine/math/Vector.h"
#include "engine/math/Matrix.h"
#include "engine/math/Quaternion.h"

// for the debug camera bindings
#include "engine/input/InputSystem.h"

PROPELLER_FORWARD_DECLARE_2(engine, scene, CameraComponent);

using namespace engine::math; //TODO: cleanup and remove this namespace here

namespace engine {
namespace renderer {

	class CameraSystem : public engine::SystemBase
	{
	public:
		enum CameraMode
		{
			CAMERAMODE_COMPONENT = 0,
			CAMERAMODE_DEBUG_FREEFLY,
		};

		DEFINE_CLASS(CameraSystem);

	private:

		math::Vec3 up;
		math::Vec3 position;
		math::Quat rotation;

		input::InputSystem *inputSystem;

		//other settings like fov, etc
		CameraMode mode;

		math::Vec3i cameraMovement;
		math::Matrix4x4 cameraMatrix;

		scene::CameraComponent *activeCameraComponent;

	public:
		CameraSystem(engine::input::InputSystem *inputSystem);

		const bool isGameplaySystem() { return false; }

		const String getName() { return "CameraSystem"; }

		bool init();
		void uninit() {};
		void update(float delta);

		const CameraMode &getCameraMode() const { return mode; }
		void setCameraMode(const CameraMode &cameraMode) { mode = cameraMode; }

		const math::Matrix4x4 &getMatrix() const;

		// Component mode stuff
		void setActive(scene::CameraComponent *cameraComponent);
		void setInactive(scene::CameraComponent *cameraComponent);

		scene::CameraComponent *getActiveCameraComponent();

		// rotating / moving
		void rotate(const float x, const float y);

		void forward(bool isKeyDown);
		void back(bool isKeyDown);
		void right(bool isKeyDown);
		void left(bool isKeyDown);

		// Getters & setters
		const Vec3 &getUp() const { return up; }
		const math::Quat &getRotation() const { return rotation; }
		const Vec3 &getPosition() const { return position; }

		void setPosition(const Vec3 &pos) { position = pos; }
		void setRotation(const math::Quat &rot) { rotation = rot; }
	};

}
}

#endif