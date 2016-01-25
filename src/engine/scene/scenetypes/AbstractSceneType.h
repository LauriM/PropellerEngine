// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_ABSTRACTSCENETYPE_H
#define ENGINE_SCENE_ABSTRACTSCENETYPE_H

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace engine {
namespace scene {

	enum SceneType
	{
		SCENE_TYPE_INVALID = 0,
		SCENE_TYPE_EDITOR,
		SCENE_TYPE_PROGRAMMABLE,
	};

	class AbstractSceneType
	{
	public:
		virtual const SceneType getSceneType() = 0;
		virtual const String getSceneName() = 0;
		virtual void loadScene(GameInstance *instance) = 0;
	};

}
}

#endif