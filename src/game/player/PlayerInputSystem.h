// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_PLAYER_PLAYERINPUTSYSTEM_H
#define GAME_PLAYER_PLAYERINPUTSYSTEM_H

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

#endif