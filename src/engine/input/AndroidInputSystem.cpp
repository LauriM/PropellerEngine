// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/input/AndroidInputSystem.h"

#ifdef OS_ANDROID

#include "engine/input/InputSystem.h"

namespace engine {
namespace input {

	AndroidInputSystem::AndroidInputSystem(InputSystem *inputSystem)
		: inputSystem(inputSystem)
		, lastPosX(0)
		, lastPosY(0)
		, touch(false)
	{ }

	bool AndroidInputSystem::init()
	{
		return true;
	}

	void AndroidInputSystem::uninit() { }

	void AndroidInputSystem::update(float delta) 
	{ 
		PROFILE;

		if (touchCheck == false)
		{
			if (touch == true)
			{
				inputSystem->keyUp(TOUCH);
				touch = false;
			}
		}

		touchCheck = false;
	}

	void AndroidInputSystem::handleTouchInput(float x, float y)
	{
		PROFILE;

		float diffX, diffY;

		touchCheck = true; // used to detect when the touch ends

		if (touch == false)
		{
			inputSystem->keyDown(TOUCH);

			// reset the start position to the start of the touch
			lastPosX = x;
			lastPosY = y;
		}

		touch = true;

		diffX = lastPosX - x;
		diffY = lastPosY - y;

		inputSystem->axisMove(TOUCH_DELTA, diffX, diffY); //TODO: check if this is handled even this way ?!
		inputSystem->setCursorPositon(math::Vec2(x, y));
	}
}
}

#endif