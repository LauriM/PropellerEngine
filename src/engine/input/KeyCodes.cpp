// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/input/KeyCodes.h"

namespace engine {
namespace input {

	const KeyCode getKeyForString(const String &str)
	{
		for (unsigned i = 0; i < NUM_KEYS; ++i)
		{
			if (strcmp(keysToString[i], str.c_str()) == 0)
				return KeyCode(i);
		}

		return KEY_VOID;
	}

	const AxisCode getAxisForString(const String &str)
	{
		for (unsigned i = 0; i < NUM_AXIS; ++i)
		{
			if (strcmp(axisToString[i], str.c_str()) == 0)
				return AxisCode(i);
		}

		return AXIS_VOID;
	}


}
}
