// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.

#include "engine/SystemBase.h"

PROPELLER_FORWARD_DECLARE_2(engine, renderer, DebugDrawSystem);

namespace editor {

	class EditorVisualizationSystem : public engine::SystemBase
	{
	private:
		engine::renderer::DebugDrawSystem *debugDrawSystem;

	public:
		EditorVisualizationSystem(engine::renderer::DebugDrawSystem *debugDrawSystem);

		const String getName() { return "EditorVisualizationSystem"; }

		const bool isGameplaySystem() { return false; }

		bool init();
		void uninit();
		void update(float delta);
	};

}