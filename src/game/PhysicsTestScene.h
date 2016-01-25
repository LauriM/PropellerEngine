// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_PHYSICSTESTSCENE_H
#define GAME_PHYSICSTESTSCENE_H

#include "engine/scene/scenetypes/ProgrammableSceneType.h"

namespace game {

	class PhysicsTestScene : public engine::scene::ProgrammableSceneType
	{
	public:
		void onSceneLoad(GameInstance *instance);

		const String getSceneName() { return "default"; }
	};

}

#endif