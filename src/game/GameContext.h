// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "game/precompiled.h"

PROPELLER_FORWARD_DECLARE_2(game, player, PlayerInputSystem);

namespace game {

	// contains the data for the gamecontext
	// Place all pointers to systems you need all around the code here.
	// This way you can easily access them everywhere, without making
	// it a global.
	//
	// If you have a pointer to GameInstance, you can get the context
	// with ->getContext() call. From that you can get the GameContext()
	// to access the ptrs in this class.
	class GameContextData
	{
	public:
		GameContextData()
			: playerInputSystem(NULL)
		{ }

		player::PlayerInputSystem *playerInputSystem;
	};

}

#endif
