#pragma once

// This is a example class for playerinput component

#include "engine/component/Component.h"
#include "engine/stream/Serializable.h"

namespace game {
namespace player {

	// look into the Component baseclass to see what you have to implement.
	class PlayerInputComponent : public engine::component::Component
	{
	public:
		// Define the component and register it to the rtti-system
		DEFINE_COMPONENT(PlayerInputComponent);

	private:
		// Local data for the component that is _NOT_ saved.
		math::Vec2 movement;

	public:
		PlayerInputComponent(void *context);
		~PlayerInputComponent();

		// These are used to serialize data for save data, look into the PickupComponent for better example
		// this component doesn't have data so it doesn't need to save anything.
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
