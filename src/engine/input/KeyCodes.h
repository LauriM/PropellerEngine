// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_INPUT_KEYCODES_H
#define ENGINE_INPUT_KEYCODES_H

namespace engine {
namespace input {

	enum KeyCode
	{
		KEY_VOID = 0,

		/* Normal keys */
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_DOT,
		KEY_COMMA,
		KEY_TILDE,
		KEY_PLUS,
		KEY_MINUS,

		/* numbers */
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,

		/* 'command' keys */

		KEY_SPACE,
		KEY_TAB,
		KEY_CAPSLOCK,
		KEY_LSIFTH,
		KEY_RSIFTH,
		KEY_LCTRL,
		KEY_RCTRL,
		KEY_LALT,
		KEY_RALT,
		KEY_BACKSPACE,
		KEY_ENTER,
		KEY_ESC,

		/* function keys */

		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,

		/* Special keys */

		KEY_INSERT,
		KEY_HOME,
		KEY_DELETE,
		KEY_END,
		KEY_PAGEUP,
		KEY_PAGEDOWN,
		KEY_PRINTSCREEN,
		KEY_SCROLLLOCK,
		KEY_PAUSE,

		/* numpad keys */

		KEY_NUM_LOCK,
		KEY_NUM_PLUS,
		KEY_NUM_MINUS,
		KEY_NUM_SUM,
		KEY_NUM_DIV,
		KEY_NUM_0,
		KEY_NUM_1,
		KEY_NUM_2,
		KEY_NUM_3,
		KEY_NUM_4,
		KEY_NUM_5,
		KEY_NUM_6,
		KEY_NUM_7,
		KEY_NUM_8,
		KEY_NUM_9,
		KEY_NUM_ENTER,
		KEY_NUM_DEL,

		/* Gamepad keys */

		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_UP,
		BUTTON_DOWN,
		BUTTON_LB,
		BUTTON_RB,
		BUTTON_BACK,
		BUTTON_START,

		/* Touch input */
		TOUCH,

		/* Mouse input */
		MOUSE_1,
		MOUSE_2,
		MOUSE_3,

		NUM_KEYS,
	};

	static const char *keysToString[NUM_KEYS] =
	{
		"KEY_VOID",
		"KEY_A",
		"KEY_B",
		"KEY_C",
		"KEY_D",
		"KEY_E",
		"KEY_F",
		"KEY_G",
		"KEY_H",
		"KEY_I",
		"KEY_J",
		"KEY_K",
		"KEY_L",
		"KEY_M",
		"KEY_N",
		"KEY_O",
		"KEY_P",
		"KEY_Q",
		"KEY_R",
		"KEY_S",
		"KEY_T",
		"KEY_U",
		"KEY_V",
		"KEY_W",
		"KEY_X",
		"KEY_Y",
		"KEY_Z",
		"KEY_DOT",
		"KEY_COMMA",
		"KEY_TILDE",
		"KEY_PLUS",
		"KEY_MINUS",
		"KEY_0",
		"KEY_1",
		"KEY_2",
		"KEY_3",
		"KEY_4",
		"KEY_5",
		"KEY_6",
		"KEY_7",
		"KEY_8",
		"KEY_9",
		"KEY_SPACE",
		"KEY_TAB",
		"KEY_CAPSLOCK",
		"KEY_LSIFTH",
		"KEY_RSIFTH",
		"KEY_LCTRL",
		"KEY_RCTRL",
		"KEY_LALT",
		"KEY_RALT",
		"KEY_BACKSPACE",
		"KEY_ENTER",
		"KEY_ESC",
		"KEY_F1",
		"KEY_F2",
		"KEY_F3",
		"KEY_F4",
		"KEY_F5",
		"KEY_F6",
		"KEY_F7",
		"KEY_F8",
		"KEY_F9",
		"KEY_F10",
		"KEY_F11",
		"KEY_F12",
		"KEY_INSERT",
		"KEY_HOME",
		"KEY_DELETE",
		"KEY_END",
		"KEY_PAGEUP",
		"KEY_PAGEDOWN",
		"KEY_PRINTSCREEN",
		"KEY_SCROLLLOCK",
		"KEY_PAUSE",
		"KEY_NUM_LOCK",
		"KEY_NUM_PLUS",
		"KEY_NUM_MINUS",
		"KEY_NUM_SUM",
		"KEY_NUM_DIV",
		"KEY_NUM_0",
		"KEY_NUM_1",
		"KEY_NUM_2",
		"KEY_NUM_3",
		"KEY_NUM_4",
		"KEY_NUM_5",
		"KEY_NUM_6",
		"KEY_NUM_7",
		"KEY_NUM_8",
		"KEY_NUM_9",
		"KEY_NUM_ENTER",
		"KEY_NUM_DEL",
		"BUTTON_A",
		"BUTTON_B",
		"BUTTON_X",
		"BUTTON_Y",
		"BUTTON_LEFT",
		"BUTTON_RIGHT",
		"BUTTON_UP",
		"BUTTON_DOWN",
		"BUTTON_LB",
		"BUTTON_RB",
		"BUTTON_BACK",
		"BUTTON_START",
		"TOUCH",
		"MOUSE_1",
		"MOUSE_2",
		"MOUSE_3",
	};

	// Axis Types
	//
	// -> delta  when a mouse or touch moves around, its delta position.
	// -> pos    absolute position of touch/mouse etc on screen.
	//
	// all input events are triggered when something happens, no input when staying still
	
	enum AxisCode
	{
		AXIS_VOID = 0,
		MOUSE,
		MOUSE_DELTA,
		TOUCH_DELTA,
		JOY_STICK_LEFT,
		JOY_STICK_RIGHT,
		NUM_AXIS,
	};

	static const char *axisToString[NUM_AXIS] =
	{
		"AXIS_VOID",
		"MOUSE",
		"MOUSE_DELTA",
		"TOUCH_DELTA",
		"JOY_STICK_LEFT",
		"JOY_STICK_RIGHT",
	};

	const KeyCode getKeyForString(const String &str);
	const AxisCode getAxisForString(const String &str);

}
}

#endif