// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/EditorVisualizationSystem.h"

//#include "engine/renderer/DebugDrawSystem.h"

namespace editor {

	EditorVisualizationSystem::EditorVisualizationSystem(engine::renderer::DebugDrawSystem *debugDrawSystem)
		: debugDrawSystem(debugDrawSystem)
	{ 
		LOG_WARNING("DebugDrawSystem has been deprecrated! Reimplement debugdrawing in the renderer");
	}

	bool EditorVisualizationSystem::init() 
	{ 
		return true;
	}

	void EditorVisualizationSystem::uninit() { }

	void EditorVisualizationSystem::update(float delta)
	{
		//debugDrawSystem->addDebugLine(engine::math::Vec3(0.f, 0.f, 0.f), engine::math::Vec3(1.f, 1.f, 1.f), engine::math::Vec3(1.f, 0.f, 0.f), engine::renderer::DebugTimerType::DEBUGTIMERTYPE_TICK, 1);
	}

}
