// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/preprocessor/platform.h"

#if defined OS_WINDOWS

#ifndef ENGINE_INPUT_XINPUTSYSTEM_H
#define ENGINE_INPUT_XINPUTSYSTEM_H

#include "engine/SystemBase.h"

#include "engine/input/KeyCodes.h"

#include <xinput.h>

PROPELLER_FORWARD_DECLARE_2(engine, input, InputSystem);

namespace engine {
namespace input {
	
	static const unsigned MAX_CONTROLLERS = 4;

	class XInputSystem : public SystemBase
	{
	private:
		InputSystem *inputSystem;

		bool controllerConnected[MAX_CONTROLLERS];
		XINPUT_STATE controllerState[MAX_CONTROLLERS];

		KeyCode xInputToKeyCode(const WORD &param);

		void handleButton(const XINPUT_STATE &oldState, const XINPUT_STATE &newState, const WORD &buttonCode);

		bool isInDeadZone(int amount);

	public:
		XInputSystem(InputSystem *inputSystem);

		const String getName() { return "XInputSystem"; }

		bool init();
		void uninit();
		void update(float delta);
	};

}
}

#endif

#endif