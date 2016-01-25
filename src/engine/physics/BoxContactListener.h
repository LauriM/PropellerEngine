// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_PHYSICS_BOXCONTACTLISTENER_H
#define ENGINE_PHYSICS_BOXCONTACTLISTENER_H

#include <Box2D/Box2D.h>

namespace engine {
namespace physics {

	class BoxContactListener : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
	};

}
}

#endif
