// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_GAMEMODE_H
#define ENGINE_GAMEMODE_H

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace engine {

	class GameMode
	{
	protected:
		GameInstance* instance;

	private:
		friend class GameInstance;
		void setInstance(GameInstance *inst) { instance = inst; }

	public:
		// Idea: onSceneLoad (sceneName)

		// Triggered after the scene has been loaded
		virtual void onSceneLoad() = 0;

		// Triggered each frame game is running
		virtual void onGameRunning() = 0;

		// Triggered just before scene is being closed
		virtual void onSceneUnload() = 0;
	};

}

#endif