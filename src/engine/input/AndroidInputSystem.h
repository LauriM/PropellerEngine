// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_INPUT_ANDROIDINPUTSYSTEM_H
#define ENGINE_INPUT_ANDROIDINPUTSYSTEM_H

#include "engine/SystemBase.h"
#include "engine/input/KeyCodes.h"

PROPELLER_FORWARD_DECLARE_2(engine, input, InputSystem);

namespace engine {
namespace input {

	class AndroidInputSystem : public engine::SystemBase
	{
	private:
		InputSystem *inputSystem;

		float lastPosX, lastPosY;
		bool touch;
		bool touchCheck;

	public:
		AndroidInputSystem(InputSystem *inputSystem);

		const String getName() { return "AndroidInputSystem"; }

		bool init();
		void uninit();
		void update(float delta);

		void handleTouchInput(float x, float y);
	};

}
}

#endif