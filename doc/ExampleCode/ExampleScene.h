// Example scene for PropellerEngine
#pragma once

#include "engine/scene/scenetypes/ProgrammableSceneType.h"

// You need to create the class and implement the two methods.
// Its more effective the keep the actual onSceneLoad on the different .cpp file.
// Remember to change the output of getSceneName() to your own name.
// Its used when the scene is loaded, so don't change it during the runtime.

namespace game {

	class ExampleScene : public engine::scene::ProgrammableSceneType
	{
	public:
		void onSceneLoad(GameInstance *instance);

		const String getSceneName() { return "examplescene"; }
	};

}