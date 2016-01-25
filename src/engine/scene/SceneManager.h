// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_SCENEMANAGER_H
#define ENGINE_SCENE_SCENEMANAGER_H

#include "engine/scene/scenetypes/AbstractSceneType.h"
#include "engine/util/Array.h"

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace engine {
namespace scene {

	class SceneManager
	{
	private:
		engine::GameInstance *instance;

		util::Array<AbstractSceneType *> scenes;

	public:
		SceneManager(engine::GameInstance *instance)
			: instance(instance)
		{ }

		~SceneManager();

		// Add scene to the manager, SceneManager handles freeing the pointer after this.
		void addScene(AbstractSceneType *scene);

		void populateScenesFromArchives();

		const unsigned getSceneCount() const { return scenes.getSize(); }

		// Loads scene into the active instance by sceneName
		void loadScene(const String &sceneName);

		const util::Array<AbstractSceneType*> &getSceneList() const { return scenes; }
	};

}
}

#endif