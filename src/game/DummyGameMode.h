// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_DUMMYGAMEMODE_H
#define GAME_DUMMYGAMEMODE_H

#include "engine/GameMode.h"
#include "engine/preprocessor/shared.h"

namespace game {

	class DummyGameMode : public engine::GameMode
	{
		// Triggered after the scene has been loaded
		void SHAREDGAME onSceneLoad();

		// Triggered each frame game is running
		void SHAREDGAME onGameRunning();

		// Triggered just before scene is being clsoed
		void SHAREDGAME onSceneUnload();
	};

}

#endif