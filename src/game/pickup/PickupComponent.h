// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_PICKUPCOMPONENT_H
#define GAME_PICKUPCOMPONENT_H

#include "engine/component/Component.h"
#include "engine/stream/Serializable.h"

PROPELLER_FORWARD_DECLARE_2(engine, physics, Box2DRigidBodyComponent);

namespace game {

	class PickupComponent : public engine::component::Component
	{
	public:
		DEFINE_COMPONENT(PickupComponent);

	public:
		PickupComponent(void *context);
		~PickupComponent();

		void init();
		void uninit();

		void save(engine::stream::OutputStream<engine::stream::SerializationEndian> &strm) const { }
		void load(engine::stream::InputStream<engine::stream::SerializationEndian> &strm) { }

		void onHit(unsigned otherHandle);
	};

}

#endif
