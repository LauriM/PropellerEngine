// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/math/Random.h"

namespace engine {
namespace math {

	int randomRange(int min, int max)
	{
		return min + (rand() % (int)(max - min + 1));
	}

}
}
