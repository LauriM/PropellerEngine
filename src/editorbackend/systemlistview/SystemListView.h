// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_SYSTEMLISTVIEW_SYSTEMLISTVIEW_H
#define EDITOR_SYSTEMLISTVIEW_SYSTEMLISTVIEW_H

#include "editorbackend/CSharp/CSharpInstance.h"

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace editor {

	class SystemListView : public CSharpInstance
	{
	private:
		engine::GameInstance *instance;

	public:
		bool init();
		void uninit() {};

		void setTargetInstance(int64_t target);

		void update();

		void refresh();

	private:
		void addSystemToGui(String systemName, bool enabled);
	};

}

#endif