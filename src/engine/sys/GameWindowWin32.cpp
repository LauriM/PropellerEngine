// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/preprocessor/platform.h"

#if defined OS_WINDOWS
#include "engine/precompiled.h"

#include "engine/sys/GameWindow.h"

#ifdef _EDITOR
#include "engine/input/InputSystem.h"
#include "engine/input/KeyCodes.h"
#endif

namespace engine {
namespace sys {

	GameWindow::GameWindow(const String &title, const int &width, const int &height)
		: windowClosed(false)
		, windowClassString("Window_" + title) //TODO: use id or something
		, inputSystem(NULL)
	{
		ZeroMemory(&windowClass, sizeof(WNDCLASS));
		windowClass.style = CS_OWNDC;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = instance;
		windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = windowClassString.c_str();
		windowClass.lpfnWndProc = (WNDPROC)staticProc;

		if (!RegisterClass(&windowClass))
			LOG_ERROR("Window class creation failed with code: " << GetLastError());

		windowHandle = CreateWindowEx(
			WS_EX_APPWINDOW,
			windowClassString.c_str(),
			title.c_str(),
			WS_OVERLAPPED | WS_SYSMENU,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			(HWND)NULL,
			(HMENU)NULL,
			instance,
			this);

		if (!windowHandle)
		{
			LOG_ERROR("Error creating window: " << GetLastError());
			windowClosed = true;
			return;
		}

		ShowWindow(windowHandle, true);

		DEBUG_PRINT("# Game window created!");
	}

	GameWindow::~GameWindow()
	{
		DestroyWindow(windowHandle);
		UnregisterClass(windowClassString.c_str(), instance); 
	}

	LRESULT CALLBACK GameWindow::staticProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		GameWindow *window;

		if(msg == WM_SETCURSOR)
		{
			/*
			if (LOWORD(lparam) == HTCLIENT)
				SetCursor(NULL);
				*/

			return true;
		}

		if (msg == WM_NCCREATE)
		{
			CREATESTRUCT *cs = (CREATESTRUCT*)lparam;
			window = (GameWindow*)cs->lpCreateParams;

			SetProp(hwnd, TEXT("gameWindowPTR"), (HANDLE)window);
		}
		else
		{
			window = (GameWindow*)GetProp(hwnd, TEXT("gameWindowPTR"));
		}

		if (window)
			return window->proc(hwnd, msg, wparam, lparam);

		return false;
	}

	LRESULT CALLBACK GameWindow::proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		GameWindow *window = (GameWindow*)GetProp(hwnd, TEXT("gameWindowPTR"));

		switch (msg){
		case WM_KEYDOWN:
			if (wparam == VK_ESCAPE) {
				window->close();
				break;
			}

#ifdef _EDITOR
			// Editor doesn't support rawinput, lets forward the window input to the inputSystem
			if (inputSystem != NULL)
				inputSystem->keyDown(engine::input::KEY_A);
#endif

			break;

		case WM_KEYUP:

#ifdef _EDITOR
			if (inputSystem != NULL)
				inputSystem->keyUp(engine::input::KEY_A);
#endif

			break;
		case WM_CLOSE:
			window->close();
			break;
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

}
}

#endif