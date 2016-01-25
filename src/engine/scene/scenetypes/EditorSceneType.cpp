// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/scene/scenetypes/EditorSceneType.h"
#include "engine/util/StringUtil.h"
#include "engine/GameInstance.h"

namespace engine {
namespace scene {

	EditorSceneType::EditorSceneType(const String fileName)
		: fileName(fileName)
	{
		std::vector<String> result;

		util::explode(&result, fileName, '.');

		name = result[0];
	}

	void EditorSceneType::loadScene(GameInstance *instance)
	{
		instance->loadSceneFromArchive(fileName);
	}

}
}