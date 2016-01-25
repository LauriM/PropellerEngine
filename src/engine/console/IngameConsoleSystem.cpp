// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/console/IngameConsoleSystem.h"
#include "engine/input/InputSystem.h"
#include "engine/resource/ResourceManager.h"
#include "engine/console/Console.h"
#include "engine/console/Cvar.h"

//TODO: move the FPS counter to a separated system?
#include "engine/GameInstance.h"

//TODO: Render disabled here

namespace cvar {
	CVAR(int, showconsole, 0, false);
	CVAR(int, showfps, 0, true);
}

namespace engine {
namespace console {

	IngameConsoleSystem::IngameConsoleSystem(renderer::TextRendererSystem *textRendererSystem, input::InputSystem *inputSystem, resource::ResourceManager *resourceManager, GameInstance *instance)
		: textRendererSystem(textRendererSystem)
		, inputSystem(inputSystem)
		, resourceManager(resourceManager)
		, instance(instance)
	{ }

	void IngameConsoleSystem::toggleConsole(bool k)
	{
		if (k == false)
			return;

		if (*cvar::showconsole)
			*cvar::showconsole = false;
		else
			*cvar::showconsole = true;

		LOG_INFO("Console toggled");
	}

	bool IngameConsoleSystem::init()
	{
		PROFILE;

		//font = dynamic_cast<renderer::FontResource*>(resourceManager->getResourceByName("Consolas.ttf"));

		if (font == NULL)
		{
			LOG_WARNING("Could not load font for ingame console!");
			stop();
			return false;
		}

		inputSystem->bindKeyEvent("toggleConsole", this, &IngameConsoleSystem::toggleConsole);

		return true;
	}

	void IngameConsoleSystem::update(float delta)
	{
		PROFILE;

		if (*cvar::showconsole)
			drawConsole();

		if (*cvar::showfps)
			drawFPS();
	}

	void IngameConsoleSystem::drawFPS()
	{
		PROFILE;

		std::stringstream ss;
		ss << "Frametime: ";
		ss << instance->getLastFrameTimeInMs();
		ss << "(ms)";

		//textRendererSystem->drawText(math::Vec2(0.f, 30.f), font, ss.str());
	}

	void IngameConsoleSystem::drawConsole()
	{
		PROFILE;

		//textRendererSystem->drawText(math::Vec2(0.f, 30.f), font, "CONSOLE IS ENABLED");

		const float stepping = 25;
		float pos = 60;

		const Console::HistoryList &history = Console::getHistoryList();

		if (history.getSize() == 0)
			return; //nothing to show

		int start = history.getSize() - 30;

		if (start < 0)
			start = 0;

		int end = start + 30;

		for (int i = start; i < end; ++i)
		{
			//textRendererSystem->drawText(math::Vec2(5.f, pos), font, history[i]);
			pos += stepping;
		}
	}

	void IngameConsoleSystem::uninit() { }

}
}
