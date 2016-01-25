// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/preprocessor/platform.h"

#if defined OS_WINDOWS

#include "engine/precompiled.h"

#include <Xinput.h>

#include "engine/input/XInputSystem.h"
#include "engine/input/InputSystem.h"
#include "engine/console/Cvar.h"

namespace cvar {
	CVAR(int, xinput_deadzone, 5500, true);
}

namespace engine {
namespace input {

	XInputSystem::XInputSystem(InputSystem *inputSystem)
		: inputSystem(inputSystem)
	{}

	bool XInputSystem::init() 
	{
		PROFILE;

		// Reset controller count
		for (unsigned i = 0; i < MAX_CONTROLLERS; ++i)
			controllerConnected[i] = false;

		// Find connected controllers
		XINPUT_STATE state;

		for (unsigned i = 0; i < MAX_CONTROLLERS; ++i)
		{
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			DWORD result = XInputGetState(i, &state);

			if (result == ERROR_SUCCESS)
			{
				controllerConnected[i] = true;
				controllerState[i] = state;
			}
		}

		unsigned count = 0;
		for (unsigned i = 0; i < MAX_CONTROLLERS; ++i)
		{
			if (controllerConnected[i])
			{
				LOG_INFO("[XInputSystem] Controller " << i + 1 << " connected");
				++count;
			}
		}

		LOG_INFO("[XInputSystem] Total of " << count << " controller(s) detected!");

		if (count == 0)
		{
			LOG_INFO("[XInputSystem] no controllers detected! Stopping XInputSystem.");
			stop();
		}

		return true;
	}

	void XInputSystem::uninit() {}

	bool XInputSystem::isInDeadZone(int amount)
	{
		if (amount < -*cvar::xinput_deadzone)
			return true;
		
		if (amount > *cvar::xinput_deadzone)
			return true;

		return false;
	}

	void XInputSystem::update(float delta)
	{
		PROFILE;

		XINPUT_STATE state;

		for (unsigned i = 0; i < MAX_CONTROLLERS; ++i)
		{
			if (controllerConnected[i])
			{
				// Get new state and compare to old

				DWORD result = XInputGetState(i, &state);

				if (result != ERROR_SUCCESS)
				{
					LOG_WARNING("[XInputSystem] Error on controller state!");
					continue;
				}

				// Handle sticks

				//QQQ the deadzone checks have not been tested to work ! TODO

				// if not in deadzone, its input
				if (isInDeadZone(controllerState[i].Gamepad.sThumbLX) || isInDeadZone(controllerState[i].Gamepad.sThumbLY))
					inputSystem->axisMove(JOY_STICK_LEFT, controllerState[i].Gamepad.sThumbLX, controllerState[i].Gamepad.sThumbLY);

				if (isInDeadZone(controllerState[i].Gamepad.sThumbRX) || isInDeadZone(controllerState[i].Gamepad.sThumbRY))
					inputSystem->axisMove(JOY_STICK_RIGHT, controllerState[i].Gamepad.sThumbRX, controllerState[i].Gamepad.sThumbRY);

				/*
				// Has the button state changed from last time?
				if (state.Gamepad.wButtons == controllerState[i].Gamepad.wButtons)
					continue; // no change, next controller
					*/

				// main buttons
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_A);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_B);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_X);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_Y);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_DPAD_DOWN);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_DPAD_UP);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_DPAD_LEFT);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_DPAD_RIGHT);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_LEFT_SHOULDER);
				handleButton(controllerState[i], state, XINPUT_GAMEPAD_RIGHT_SHOULDER);

				// throw old state in
				controllerState[i] = state;
			}
		}
	}

	void XInputSystem::handleButton(const XINPUT_STATE &oldState, const XINPUT_STATE &newState, const WORD &buttonCode)
	{
		if ((oldState.Gamepad.wButtons & buttonCode) != (newState.Gamepad.wButtons & buttonCode))
		{
			if (newState.Gamepad.wButtons & buttonCode)
			{
				// down
				inputSystem->keyDown(xInputToKeyCode(buttonCode));
			}
			else
			{
				// up
				inputSystem->keyUp(xInputToKeyCode(buttonCode));
			}

		}
	}

	KeyCode XInputSystem::xInputToKeyCode(const WORD &param)
	{
		switch (param)
		{
		case XINPUT_GAMEPAD_A:
			return BUTTON_A;
		case XINPUT_GAMEPAD_B:
			return BUTTON_B;
		case XINPUT_GAMEPAD_X:
			return BUTTON_X;
		case XINPUT_GAMEPAD_Y:
			return BUTTON_Y;
		case XINPUT_GAMEPAD_DPAD_UP:
			return BUTTON_UP;
		case XINPUT_GAMEPAD_DPAD_DOWN:
			return BUTTON_DOWN;
		case XINPUT_GAMEPAD_DPAD_LEFT:
			return BUTTON_LEFT;
		case XINPUT_GAMEPAD_DPAD_RIGHT:
			return BUTTON_RIGHT;
		case XINPUT_GAMEPAD_LEFT_SHOULDER:
			return BUTTON_LB;
		case XINPUT_GAMEPAD_RIGHT_SHOULDER:
			return BUTTON_RB;
		}

		return KEY_VOID;
	}
}
}

#endif