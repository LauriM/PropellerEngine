// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_DUMMYGAMEINSTANCE_H
#define GAME_DUMMYGAMEINSTANCE_H

#include "engine/GameInstance.h"
#include "engine/preprocessor/shared.h"
#include "game/GameContext.h"

PROPELLER_FORWARD_DECLARE_2(game, player, PlayerInputSystem);

namespace game {

	class DummyGameInstance : public engine::GameInstance
	{
	private:
		player::PlayerInputSystem *playerInputSystem;

		GameContextData gameContext;

	public:
		bool SHAREDGAME gameInit();
		void SHAREDGAME gameUninit();

		GameContextData *getGameContextData() { return &gameContext; }
	};

}

#endif