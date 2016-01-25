// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/scene/SceneManager.h"
#include "engine/scene/scenetypes/AbstractSceneType.h"
#include "engine/GameInstance.h"
#include "engine/file/FileManager.h"
#include "engine/scene/scenetypes/EditorSceneType.h"
#include "engine/console/Cvar.h"

namespace cvar {
	CVAR(String, defaultScene, "default", false);
}


namespace command {

	CREATE_COMMAND(scenes, "List all scenes")
	{
		for (unsigned i = 0; i < instance->getSceneManager()->getSceneList().getSize(); ++i)
			LOG_INFO(" > " << instance->getSceneManager()->getSceneList()[i]->getSceneName());

		return 0;
	}

}

namespace engine {
namespace scene {

	SceneManager::~SceneManager()
	{
		// Removing programmable scenes and editorscenes
		for (unsigned i = 0; i < scenes.getSize(); ++i)
		{
			delete scenes[i];
		}
	}

	void SceneManager::addScene(AbstractSceneType *scene)
	{
		scenes.push(scene);
		LOG_INFO("[SceneManager] Scene '" << scene->getSceneName() << "' registered");
	}

	void SceneManager::populateScenesFromArchives()
	{
		PROFILE;

		LOG_INFO("[SceneManager] Populating scene list...");

		file::FileList fileList;
		instance->getFileManager()->listFiles(fileList);

		for (unsigned i = 0; i < fileList.getSize(); ++i)
		{
			if (fileList[i].find(".PropellerScene") != String::npos)
			{
				addScene(new EditorSceneType(fileList[i]));
			}
		}

		LOG_INFO("[SceneManager] Scene list populated!");
	}

	void SceneManager::loadScene(const String &sceneName)
	{
		PROFILE;

		for (unsigned i = 0; i < scenes.getSize(); ++i)
		{
			if (scenes[i]->getSceneName() == sceneName)
			{
				scenes[i]->loadScene(instance);
				instance->sceneRefresh();
				LOG_INFO("[SceneManager] Scene loaded!");
				return;
			}
		}

		LOG_WARNING("[SceneManager] Could not found the scene: " << sceneName);
	}

}
}