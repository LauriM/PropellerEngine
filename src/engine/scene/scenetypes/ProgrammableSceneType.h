// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_PROGRAMMABLESCENETYPE_H
#define ENGINE_SCENE_PROGRAMMABLESCENETYPE_H

#include "engine/scene/scenetypes/AbstractSceneType.h"

namespace engine {
namespace scene {

	class ProgrammableSceneType : public AbstractSceneType
	{
	public:
		const SceneType getSceneType() { return SCENE_TYPE_PROGRAMMABLE; }

		//TODO: could this be done with one load method?
		void loadScene(GameInstance *instance)
		{
			onSceneLoad(instance);
		}

		virtual void onSceneLoad(GameInstance *instance) = 0;
	};

}
}

#endif