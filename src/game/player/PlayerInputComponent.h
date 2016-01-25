// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef GAME_PLAYER_PLAYERINPUTCOMPONENT_H
#define GAME_PLAYER_PLAYERINPUTCOMPONENT_H

#include "engine/component/Component.h"
#include "engine/stream/Serializable.h"

PROPELLER_FORWARD_DECLARE_2(engine, input, InputSystem);

namespace game {
namespace player {

	class PlayerInputComponent : public engine::component::Component
	{
	public:
		DEFINE_COMPONENT(PlayerInputComponent);

	private:
		// current movement to some direction
		math::Vec2 movement;

	public:
		PlayerInputComponent(void *context);
		~PlayerInputComponent();

		void move(float x, float y);

		void save(engine::stream::OutputStream<engine::stream::SerializationEndian> &strm) const { }
		void load(engine::stream::InputStream<engine::stream::SerializationEndian> &strm) { }

		void moveUp(bool k);
		void moveDown(bool k);
		void moveLeft(bool k);
		void moveRight(bool k);

		void playerTouch(bool v);

		const math::Vec2 &getMovement() const { return movement; }
	};

}
}

#endif