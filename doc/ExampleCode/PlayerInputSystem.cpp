// important to remember this
#include "game/precompiled.h"

#include "game/player/PlayerInputSystem.h"
#include "game/player/PlayerInputComponent.h"
#include "engine/component/ComponentHolder.h"
#include "engine/physics/Box2DCharacterComponent.h"

namespace game {
namespace player {

	// this system doesn't have any special init() or uninit() functionality.
	// they could be used to load stuff needed by the system, etc.
	bool PlayerInputSystem::init()
	{
		return true;
	}

	void PlayerInputSystem::uninit() { }

	void PlayerInputSystem::update(float delta)
	{
		// Adding PROFILE to a function adds the function to the PropellerProfiler. This can be used to easily diagnose performance issues on any platform.
		PROFILE;

		// the PlayerInputComponent had some parts where the force was applied as impulse directly.
		// this is a example of handling the constant movement per tick.
		// as you cannot loop the components, you cannot do anything that lasts over frames there.
		// System update() is called constantly, so you can handle stuff that needs to be update every 
		// tick with it.
		// Remember to handle the "delta" time! or your system will fuck up everything with different
		// devices.

		// this code is not tested and should be just used as a reference on how the components-systems works
		for (unsigned i = 0; i < components.size(); ++i)
		{
			PlayerInputComponent *inputComponent = rtti::dynamicCast<PlayerInputComponent>(components[i]);

			physics::Box2DCharacterComponent *rigidBody = inputComponent->getParent()->findComponent<physics::Box2DCharacterComponent>();

			const math::Vec2 &movement = inputComponent->getMovement();

			// Apply force
			rigidBody->applyForce(movement * delta); // deltatime applied to the force!
		}
	}

}
}