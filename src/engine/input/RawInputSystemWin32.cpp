// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/preprocessor/platform.h"

#if defined OS_WINDOWS

#include "engine/precompiled.h"

#include "engine/input/RawInputSystem.h"
#include "engine/input/InputSystem.h"

#include <WinUser.h>
#include <windowsx.h> //to get the low/high bit on the lparam

namespace engine {
namespace input {

	RawInputSystem::RawInputSystem(InputSystem *inputSystem, void *hwnd)
		: inputSystem(inputSystem)
		, mouseX(0)
		, mouseY(0)
		, lastX(0)
		, lastY(0)
		, windowHandle((HWND)hwnd)
	{ }

	bool RawInputSystem::init()
	{
		initWinKeyTable();

#ifndef _EDITOR
		RAWINPUTDEVICE device;
		device.usUsagePage = 0x01;
		device.usUsage = 0x02;
		device.dwFlags = 0;
		device.hwndTarget = NULL;
		RegisterRawInputDevices(&device, 1, sizeof(device));
		DWORD error = GetLastError();

		UINT nDevices;
		PRAWINPUTDEVICELIST pRawInputDeviceList = PRAWINPUTDEVICELIST();
		GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST));

		LOG_INFO("Total of " << nDevices << " input devices detected!");

		free(pRawInputDeviceList);
#endif

		return true;
	}

	void RawInputSystem::uninit() {}

	void RawInputSystem::update(float delta)
	{
		PROFILE;

		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			switch (msg.message) // RAW INPUT
			{
			case WM_INPUT:
				handleRawInput(msg);
				break;
			case WM_KEYDOWN:
				if (!(msg.lParam & 0x40000000)) // check the repeat count bit.
					keyDown(msg);
				break;
			case WM_KEYUP:
				keyUp(msg);
				break;
			}
		}

		POINT cursorPos;
		RECT windowRect;

		GetCursorPos(&cursorPos);
		GetWindowRect(windowHandle, &windowRect);

		int x = (int)cursorPos.x - windowRect.left;
		int y = (int)cursorPos.y - windowRect.top;

		if (lastX != x || lastY != y)
		{
			inputSystem->axisMove(MOUSE, float(x), float(y));
			inputSystem->setCursorPositon(math::Vec2(float(x), float(y)));

			lastX = x;
			lastY = y;
		}
	}

	KeyCode RawInputSystem::winkeyToKeyCode(const WPARAM &param)
	{
		return winkeyConvertTable[param];
	}

	void RawInputSystem::keyDown(const MSG &msg)
	{
		inputSystem->keyDown(winkeyToKeyCode(msg.wParam));
	}

	void RawInputSystem::keyUp(const MSG &msg)
	{
		inputSystem->keyUp(winkeyToKeyCode(msg.wParam));
	}
	
	void RawInputSystem::initWinKeyTable()
	{
		// Reset the table
		for (unsigned i = 0; i < sizeof(winkeyConvertTable) / sizeof(winkeyConvertTable[0]); ++i)
			winkeyConvertTable[i] = KEY_VOID;

		//TODO: fill this conversion table...

		winkeyConvertTable[VK_SPACE] = KEY_SPACE;
		winkeyConvertTable[VK_ESCAPE] = KEY_ESC;
		winkeyConvertTable[0x30] = KEY_0;
		winkeyConvertTable[0x31] = KEY_1;
		winkeyConvertTable[0x32] = KEY_2;
		winkeyConvertTable[0x33] = KEY_3;
		winkeyConvertTable[0x34] = KEY_4;
		winkeyConvertTable[0x35] = KEY_5;
		winkeyConvertTable[0x36] = KEY_6;
		winkeyConvertTable[0x37] = KEY_7;
		winkeyConvertTable[0x38] = KEY_8;
		winkeyConvertTable[0x39] = KEY_9;

		winkeyConvertTable[0x41] = KEY_A;
		winkeyConvertTable[0x42] = KEY_B;
		winkeyConvertTable[0x43] = KEY_C;
		winkeyConvertTable[0x44] = KEY_D;
		winkeyConvertTable[0x45] = KEY_E;
		winkeyConvertTable[0x46] = KEY_F;
		winkeyConvertTable[0x47] = KEY_G;
		winkeyConvertTable[0x48] = KEY_H;
		winkeyConvertTable[0x49] = KEY_I;

		winkeyConvertTable[0x4A] = KEY_J;
		winkeyConvertTable[0x4B] = KEY_K;
		winkeyConvertTable[0x4C] = KEY_L;
		winkeyConvertTable[0x4D] = KEY_M;
		winkeyConvertTable[0x4E] = KEY_N;
		winkeyConvertTable[0x4F] = KEY_O;
		winkeyConvertTable[0x50] = KEY_P;
		winkeyConvertTable[0x51] = KEY_Q;
		winkeyConvertTable[0x52] = KEY_R;
		winkeyConvertTable[0x53] = KEY_S;

		winkeyConvertTable[0x54] = KEY_T;
		winkeyConvertTable[0x55] = KEY_U;
		winkeyConvertTable[0x56] = KEY_V;
		winkeyConvertTable[0x57] = KEY_W;
		winkeyConvertTable[0x58] = KEY_X;
		winkeyConvertTable[0x59] = KEY_Y;
		winkeyConvertTable[0x5A] = KEY_Z;
	}

	void RawInputSystem::handleRawInput(const MSG &msg)
	{
		PROFILE;

		char buffer[sizeof(RAWINPUT)] = {};
		UINT size = sizeof(RAWINPUT);

		GetRawInputData(reinterpret_cast<HRAWINPUT>(msg.lParam), RID_INPUT, buffer, &size, sizeof(RAWINPUTHEADER));

		// extract keyboard raw input data
		RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(buffer);
		if (raw->header.dwType == RIM_TYPEKEYBOARD)
		{
			//const RAWKEYBOARD& rawKB = raw->data.keyboard;
			DEBUG_PRINT("Keyboard!");
		}

		if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			const RAWMOUSE &rawMouse = raw->data.mouse;

			inputSystem->axisMove(MOUSE_DELTA, float(rawMouse.lLastX), float(rawMouse.lLastY));

			if (rawMouse.ulButtons == RI_MOUSE_LEFT_BUTTON_DOWN)
				inputSystem->keyDown(MOUSE_1);

			if (rawMouse.ulButtons == RI_MOUSE_LEFT_BUTTON_UP)
				inputSystem->keyUp(MOUSE_1);

			if (rawMouse.ulButtons == RI_MOUSE_RIGHT_BUTTON_DOWN)
				inputSystem->keyDown(MOUSE_2);

			if (rawMouse.ulButtons == RI_MOUSE_RIGHT_BUTTON_UP)
				inputSystem->keyUp(MOUSE_2);

			if (rawMouse.ulButtons == RI_MOUSE_MIDDLE_BUTTON_DOWN)
				inputSystem->keyDown(MOUSE_3);

			if (rawMouse.ulButtons == RI_MOUSE_MIDDLE_BUTTON_UP)
				inputSystem->keyUp(MOUSE_3);
		}
	}

}
}

#endif