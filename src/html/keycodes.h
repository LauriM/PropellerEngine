#ifndef HTML_KEYCODES_H
#define HTML_KEYCODES_H

#include "engine/input/KeyCodes.h"

engine::input::KeyCode webkeyToPropellerKey[220];

void setupKeys()
{
	for (unsigned i = 0; i < 220; ++i)
		webkeyToPropellerKey[i] = engine::input::KEY_VOID;

	webkeyToPropellerKey[87] = engine::input::KEY_W;
	webkeyToPropellerKey[65] = engine::input::KEY_A;
	webkeyToPropellerKey[83] = engine::input::KEY_S;
	webkeyToPropellerKey[68] = engine::input::KEY_D;
}

#endif