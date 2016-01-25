// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_STATSVIEW_STATSVIEW_H
#define EDITOR_STATSVIEW_STATSVIEW_H

#include "editorbackend/CSharp/CSharpInstance.h"

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace editor {

	class StatsView : public CSharpInstance
	{
	private:
		engine::GameInstance *instance;

		int timer;

	public:
		bool init();
		void uninit() {};

		void setTargetInstance(int64_t target);

		void update();

	private:
		void addPoint(const String &serie, double value);

	};

}

#endif