// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_INPUT_INPUTSYSTEM_H
#define ENGINE_INPUT_INPUTSYSTEM_H

#include "engine/SystemBase.h"
#include "engine/input/KeyCodes.h"
#include "engine/console/Console.h"
#include "engine/console/Command.h"
#include "engine/util/Bind.h"
#include "engine/math/Vector.h"
#include "engine/util/HashMap.h"
#include "engine/util/Array.h"

namespace engine {
namespace input {

	class InputSystem : public SystemBase
	{
	private:
		// axis current position, used for delta calculations / requesting it from different systems
		math::Vec2 axisPosition[NUM_AXIS];

		// List of all actions available, stored here ( both axis and key stuff )
		util::HashMap<util::BindBase*, 32> actionList;

		// Contains links between keys and actions, only ptrs to the actual binds
		util::BindBase *keyBinds[NUM_KEYS];
		String stringKeyBind[NUM_KEYS];

		util::BindBase *axisBinds[NUM_AXIS];
		String stringAxisBind[NUM_AXIS];

		// Stores the current cursor position that some systems may request on demand (even when input actions are not happening)
		math::Vec2 cursorPosition;

	public:
		InputSystem();
		~InputSystem();

		const String getName() { return "InputSystem"; }

		const bool isGameplaySystem() { return false; }

		// Events from other systems
		void keyDown(KeyCode code);
		void keyUp(KeyCode code);
		void axisMove(AxisCode axis, float x, float y);

		bool init();
		void uninit();
		void update(float delta);

		//TODO:
		// getMousePosition()
		// getTouchPosition() ?

		// save all binds
		void saveToFile(const String &filename);

		// bind key to a event
		void bindKey(const String &key, const String &action);
		// bind axis to a event
		void bindAxis(const String &key, const String &action);

		// bind action to event
		template <typename ClassT>
		void bindKeyEvent(const String &name, ClassT *obj, void (ClassT::*func)(bool))
		{
			util::Bind_1<ClassT, bool> *bind = new util::Bind_1<ClassT, bool>();
			bind->name = name;
			bind->obj = obj;
			bind->func = func;

			actionList.insert(name.c_str(), bind);

			// Apply to user setting, if one is set
			for (unsigned i = 0; i < NUM_KEYS; ++i)
			{
				if (String(stringKeyBind[i]) == name)
				{
					KeyCode key = KeyCode(i);

					keyBinds[key] = bind;
				}
			}
		}

		template <typename ClassT>
		void bindAxisEvent(const String &name, ClassT *obj, void (ClassT::*func)(float, float))
		{
			util::Bind_2<ClassT, float, float> *bind = new util::Bind_2<ClassT, float, float>();
			bind->name = name;
			bind->obj = obj;
			bind->func = func;

			actionList.insert(name.c_str(), bind);

			// Apply to user setting, if one is set
			for (unsigned i = 0; i < NUM_AXIS; ++i)
			{
				if (String(stringAxisBind[i]) == name)
				{
					AxisCode axis = AxisCode(i);

					axisBinds[axis] = bind;
				}
			}
		}

		void dumpActiveBinds(util::Array<String> &binds);

		void setCursorPositon(const math::Vec2 &pos) { cursorPosition = pos; }
		const math::Vec2 &getCursorPosition() const { return cursorPosition; }

	};

}
}

#endif