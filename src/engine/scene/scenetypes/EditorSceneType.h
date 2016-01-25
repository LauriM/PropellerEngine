// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_EDITORSCENETYPE_H
#define ENGINE_SCENE_EDITORSCENETYPE_H

#include "engine/scene/scenetypes/AbstractSceneType.h"

namespace engine {
namespace scene {

	class EditorSceneType : public AbstractSceneType
	{
	private:
		String fileName; //full file name
		String name;     //name without the filetype

	public:
		EditorSceneType(const String fileName);

		const SceneType getSceneType() { return SCENE_TYPE_EDITOR; }
		const String getSceneName() { return name; }

		void loadScene(GameInstance *instance);
	};

}
}

#endif