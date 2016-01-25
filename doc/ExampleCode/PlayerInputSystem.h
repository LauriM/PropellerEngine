#pragma once

// really simple definition for a system without state.
// if you want to keep state around, just add fields for the class.
// serializing systems is not yet implemented, if this is something you need,
// ping the engine developer.

#include "engine/SystemBase.h"

namespace game {
namespace player {

	class PlayerInputSystem : public engine::SystemBase
	{
	private:

	public:
		const String getName() { return "PlayerInputSystem"; }

		bool init();
		void uninit();
		void update(float delta);
	};

}
}