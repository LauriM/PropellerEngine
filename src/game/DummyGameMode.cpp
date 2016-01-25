// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "engine/scene/Scene.h"
#include "engine/GameInstance.h"
#include "game/DummyGameMode.h"

#include "game/DummyGameInstance.h"

namespace game {

	void DummyGameMode::onSceneLoad() 
	{ 
	}

	void DummyGameMode::onGameRunning() 
	{

	}

	void DummyGameMode::onSceneUnload()
	{
		LOG_INFO("on scene unload");
	}
}
