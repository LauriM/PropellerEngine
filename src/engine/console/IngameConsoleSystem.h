// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_CONSOLE_INGAMECONSOLESYSTEM_H
#define ENGINE_CONSOLE_INGAMECONSOLESYSTEM_H

#include "engine/SystemBase.h"

PROPELLER_FORWARD_DECLARE_2(engine, renderer, TextRendererSystem);
PROPELLER_FORWARD_DECLARE_2(engine, input, InputSystem);
PROPELLER_FORWARD_DECLARE_2(engine, resource, ResourceManager);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, FontResource);
PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace engine {
namespace console {

	class IngameConsoleSystem : public SystemBase
	{
	private:
		renderer::TextRendererSystem *textRendererSystem;
		input::InputSystem *inputSystem;
		resource::ResourceManager *resourceManager;
		GameInstance *instance;

		renderer::FontResource *font;

	public:
		IngameConsoleSystem(renderer::TextRendererSystem *textRendererSystem, input::InputSystem *inputSystem, resource::ResourceManager *resourceManager, GameInstance *instance);

		const bool isGameplaySystem() { return false; }
		const bool isRendererSystem() { return true; }

		bool init();
		void update(float delta);
		void uninit();

		const String getName() { return "IngameConsoleSystem"; }

		void toggleConsole(bool k);

	private:
		void drawConsole();
		void drawFPS();
	};

}
}

#endif
