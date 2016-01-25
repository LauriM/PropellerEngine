// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_INPUT_RAWINPUTSYSTEM_H
#define ENGINE_INPUT_RAWINPUTSYSTEM_H

#include "engine/SystemBase.h"
#include "engine/input/InputSystem.h"
#include "engine/input/KeyCodes.h"

namespace engine {
namespace input {

	class RawInputSystem : public engine::SystemBase
	{
	private:
		InputSystem *inputSystem;

#if defined OS_WINDOWS
		HWND windowHandle;

		// Last mouse positions to prevent MOUSE-event spam
		int lastX, lastY;

		KeyCode winkeyConvertTable[376];
		KeyCode winkeyToKeyCode(const WPARAM &param);

		void initWinKeyTable();

		void handleRawInput(const MSG &msg);

		// convert and forward keys
		void keyDown(const MSG &msg);
		void keyUp(const MSG &msg);
#endif

		int mouseX;
		int mouseY;

	public:
		RawInputSystem(InputSystem *inputSystem, void *hwnd);

		const bool isGameplaySystem() { return false; }

		const String getName() { return "RawInputSystem"; }

		bool init();
		void uninit();
		void update(float delta);
	};

}
}

#endif