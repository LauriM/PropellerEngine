// always remember to include this
#include "game/precompiled.h"

#include "engine/component/ComponentHolder.h"
#include "game/player/PlayerInputComponent.h"
#include "engine/input/InputSystem.h"
#include "engine/physics/Box2DRigidBodyComponent.h"
#include "engine/console/Cvar.h"
#include "game/GameContext.h"
#include "game/player/PlayerInputSystem.h"

// Accessing external cvars in this .cpp file
namespace cvar {
	EXTERN_CVAR(int, r_width);
	EXTERN_CVAR(int, r_height);
}

namespace game {
namespace player {

	// Important, used to register the class correctly to the rtti-system
	DECLARE_CLASS(PlayerInputComponent, engine::component::Component);

	// list dependencies of other components that the PlayerInputComponent requires
	BEGIN_DEPENDENCIES(PlayerInputComponent)
		REQUIRE_COMPONENT(TransformComponent);
		REQUIRE_COMPONENT(Box2DRigidBodyComponent);
	END_DEPENDENCIES;

	// Constructor, has to have the (void *context)
	PlayerInputComponent::PlayerInputComponent(void *context)
		: Component(context)
		, movement(math::Vec2(0.f, 0.f))
	{
		if (!isContextValid())
			return; // Important ! checks that the context is valid before doing anything
		            // RTTI system generates one temporary object of each class.

		// Register this component
		getGameContext()->playerInputSystem->addComponent(this);

		// This binds inputsystem key events to methods in this class.
		// If player triggers some action (playerup) the moveUp() method is called in this component
		// InputSystem itself handles keybinds to the action bindings.
		getInputSystem()->bindAxisEvent("playermovement", this, &PlayerInputComponent::move);
		getInputSystem()->bindKeyEvent("playerup", this, &PlayerInputComponent::moveUp);
		getInputSystem()->bindKeyEvent("playerdown", this, &PlayerInputComponent::moveDown);
		getInputSystem()->bindKeyEvent("playerleft", this, &PlayerInputComponent::moveLeft);
		getInputSystem()->bindKeyEvent("playerright", this, &PlayerInputComponent::moveRight);
		getInputSystem()->bindKeyEvent("playerTouch", this, &PlayerInputComponent::playerTouch);
	}

	PlayerInputComponent::~PlayerInputComponent()
	{
		if (!isContextValid()) //important check! same as in constructor
			return;

		// Unregister the component from its system, important to make sure it tries not to use components that are destroyed.
		getGameContext()->playerInputSystem->removeComponent(this);

		// yeh, the bindKeyEvents are still around and cannot be removed, Ping the engine developer if this is still an issue. (!)
		// Should be "minor fix"
		LOG_INFO("unbinding player input NOT IMPLEMENTED!");
	}

	// then just some regular c++ code to handle the movement
	void PlayerInputComponent::move(float x, float y)
	{
		// getParent() provides the entity, with the entity you can use the findComponent to find the PhysicsComponent
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (rigidBody == NULL)
			return;

		// with the rigidbody, we can apply the movement impulse. Box2dPhysicsSystem later then handles this.
		rigidBody->applyImpulse(math::Vec2(x, -10));
	}

	void PlayerInputComponent::moveUp(bool k) 
	{ 
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		if (k)
			rigidBody->applyImpulse(math::Vec2(0, 70));
	} 

	void PlayerInputComponent::moveDown(bool k) { }

	// This kind of movement has constant movement that is then handled per tick, instead of per event
	// PlayerInputSystem later reads the movement value and handles it.
	void PlayerInputComponent::moveLeft(bool k)
	{
		if (k)
			--movement.x;
		else
			++movement.x;
	}

	void PlayerInputComponent::moveRight(bool k)
	{
		if (k)
			++movement.x;
		else
			--movement.x;
	}

	void PlayerInputComponent::playerTouch(bool v)
	{
		physics::Box2DRigidBodyComponent *rigidBody = getParent()->findComponent<physics::Box2DRigidBodyComponent>();

		const math::Vec2 &cursorPos = getInputSystem()->getCursorPosition();

		math::Vec2 impulse;

		if (cursorPos.x < (*cvar::r_width / 2))
			impulse.x = -100;
		else
			impulse.x = 100;

		if (cursorPos.y < (*cvar::r_height / 2))
			impulse.y = 100;
		else
			impulse.y = -100;

		if (v)
			rigidBody->applyImpulse(impulse);
	}

}
}

