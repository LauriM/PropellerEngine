// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/statsview/StatsView.h"
#include "editorbackend/CSharp/CSharpInstanceManager.h"

#include "engine/GameInstance.h"
#include "editorbackend/GameEditor.h"
#include "engine/SystemManager.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(StatsView);

	bool StatsView::init()
	{
		registerEvent("update", this, &StatsView::update);
		registerEvent("setTargetInstance", this, &StatsView::setTargetInstance);

		LOG_INFO("Starting statsView");
		return true;
	}

	void StatsView::setTargetInstance(int64_t target) { instance = dynamic_cast<engine::GameInstance*>(((GameEditor*)target)->getGameInstance()); }

	void StatsView::update()
	{
		if (instance == NULL) //So that the first updates won't die before the target has run
			return;

		--timer;
		if (timer < 0)
		{
			addPoint("entityCount", double(instance->getScene()->getEntityList()->size()));
			//addPoint("fps", double(instance->getFPS()));

			// Get system timings

			const engine::SystemManager::SystemList systems = instance->getSystemManager()->getSystemList();

			for (unsigned i = 0; i < systems.size(); ++i)
				if (systems[i]->isRunning())
					addPoint(systems[i]->getName(), systems[i]->getTiming());

			timer = 130;
		}
	}

	void StatsView::addPoint(const String &serie, double value)
	{
		call("addPoint", serie, value);
	}

}