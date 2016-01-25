// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/physics/BulletDebugDraw.h"

#include "engine/math/VectorConversions.h"

#if defined (RENDERING_ENABLED)

namespace engine {
namespace physics {

	void BulletDebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		// Android port, disabling these for now
		/*
		debugDrawSystem->addDebugLine(math::Vec3(from.getX(), from.getY(), from.getZ()), math::Vec3(to.getX(), from.getY(), from.getZ()), math::Vec3(color.getX(), color.getY(), color.getZ()), renderer::DEBUGTIMERTYPE_TICK, 1);

		debugDrawSystem->addDebugLine(math::btVecToVec(from), math::btVecToVec(from) + math::Vec3(1,1,1), math::Vec3(color.getX(), color.getY(), color.getZ()), renderer::DEBUGTIMERTYPE_TICK, 1);
		debugDrawSystem->addDebugLine(math::btVecToVec(to), math::btVecToVec(to) + math::Vec3(-1, -1, -1), math::Vec3(color.getX(), color.getY(), color.getZ()), renderer::DEBUGTIMERTYPE_TICK, 1);
		*/
	}

	void BulletDebugDraw::reportErrorWarning(const char* warningString)
	{
		LOG_WARNING("[BulletPhysics] " << warningString);
	}

}
}

#endif
