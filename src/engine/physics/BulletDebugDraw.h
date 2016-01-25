// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PHYSICS_BULLETDEBUGDRAW_H
#define ENGINE_PHYSICS_BULLETDEBUGDRAW_H

#include <btBulletDynamicsCommon.h>

PROPELLER_FORWARD_DECLARE_2(engine, renderer, DebugDrawSystem);

namespace engine {
namespace physics {

#if defined (RENDERING_ENABLED)

	class BulletDebugDraw : public btIDebugDraw
	{
	private:
		engine::renderer::DebugDrawSystem *debugDrawSystem;

		int debugMode;

	public:
		BulletDebugDraw(renderer::DebugDrawSystem *debugDrawSystem)
			: debugDrawSystem(debugDrawSystem)
			, debugMode(DBG_MAX_DEBUG_DRAW_MODE)
		{ }

		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

		void reportErrorWarning(const char* warningString);

		void setDebugMode(int d) { debugMode = d; }
		int	getDebugMode() const { return debugMode; }

		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) { };
		void draw3dText(const btVector3& location, const char* textString) { };
	};

#endif

}
}

#endif
