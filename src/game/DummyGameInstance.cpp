// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "game/precompiled.h"

#include "game/DummyGameInstance.h"
#include "game/DummyGameMode.h"
#include "game/player/PlayerInputComponent.h"
#include "engine/scene/SceneManager.h"
#include "game/player/PlayerInputSystem.h"

// scenes
#include "game/DummyScene.h"
#include "game/PhysicsTestScene.h"

namespace game {

	bool DummyGameInstance::gameInit()
	{
		PROFILE;
		playerInputSystem = new player::PlayerInputSystem();

		systemManager.addSystem(playerInputSystem, 7);

		this->setGameMode(new DummyGameMode());

		//Register programmable scenes
		sceneManager->addScene(new DummyScene());
		sceneManager->addScene(new PhysicsTestScene());

		// Build the game context
		gameContext.playerInputSystem = playerInputSystem;

		// Provide the engine with the game's custom context
		context.gameContext = &gameContext;

		return true;
	}

	void DummyGameInstance::gameUninit()
	{
		PROFILE;
	}

}
