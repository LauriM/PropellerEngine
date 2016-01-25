// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_DUMMYSCENE_H
#define GAME_DUMMYSCENE_H

#include "engine/scene/scenetypes/ProgrammableSceneType.h"

namespace game {

	class DummyScene : public engine::scene::ProgrammableSceneType
	{
	public:
		void onSceneLoad(GameInstance *instance);

		const String getSceneName() { return "dummy"; }
	};

}

#endif