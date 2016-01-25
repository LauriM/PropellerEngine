#ifndef ENGINE_MATH_VECTORCONVERSION_H
#define ENGINE_MATH_VECTORCONVERSION_H

#include "engine/math/Vector.h"

#include <Bullet3Common/b3Vector3.h>

namespace engine {
namespace math {

	inline Vec3 btVecToVec(const btVector3 &v)
	{
		return Vec3(v.getX(), v.getY(), v.getZ());
	}

	inline btVector3 VecTobtVec(const Vec3 &v)
	{
		return btVector3(v.x, v.y, v.z);
	}

}
}

#endif