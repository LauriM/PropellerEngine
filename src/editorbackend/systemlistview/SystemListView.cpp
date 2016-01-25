// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "editorbackend/systemlistview/SystemListView.h"
#include "engine/GameInstance.h"
#include "editorbackend/GameEditor.h"
#include "engine/SystemManager.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(SystemListView);

	bool SystemListView::init()
	{
		registerEvent("refresh", this, &SystemListView::refresh);
		registerEvent("setTargetInstance", this, &SystemListView::setTargetInstance);

		LOG_INFO("Starting SystemListView");

		return true;
	}

	void SystemListView::setTargetInstance(int64_t target) 
	{
		instance = dynamic_cast<engine::GameInstance*>(((GameEditor*)target)->getGameInstance()); 
	}

	void SystemListView::refresh()
	{
		engine::SystemManager::SystemList list = instance->getSystemManager()->getSystemList();

		for (unsigned i = 0; i < list.size(); ++i)
		{
			addSystemToGui(list[i]->getName(), list[i]->isRunning());
		}
	}

	void SystemListView::addSystemToGui(String systemName, bool enabled)
	{
		call("addSystem", systemName, enabled);
	}

}