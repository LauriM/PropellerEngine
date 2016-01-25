// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H

// ptr for the context in the game side
PROPELLER_FORWARD_DECLARE_1(game, GameContextData);

// Ptrs for the ptrs in the context
PROPELLER_FORWARD_DECLARE_2(engine, physics, PhysicSystem);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, RendererSystem);
PROPELLER_FORWARD_DECLARE_2(engine, input, InputSystem);
PROPELLER_FORWARD_DECLARE_2(engine, lang, HandleManager);
PROPELLER_FORWARD_DECLARE_2(engine, physics, Box2DPhysicSystem);
PROPELLER_FORWARD_DECLARE_2(engine, resource, ResourceManager);
PROPELLER_FORWARD_DECLARE_2(engine, renderer, CameraSystem);
PROPELLER_FORWARD_DECLARE_2(engine, sys, Scheduler);
PROPELLER_FORWARD_DECLARE_2(engine, scene, Scene);

namespace engine {

	// ContextData contains the context of the engine.
	// ContextData is given to "Context" that has the getters
	struct ContextData
	{
		ContextData()
			: gameContext(NULL)
			, physicSystem(NULL)
			, box2dPhysicSystem(NULL)
			, rendererSystem(NULL)
			, inputSystem(NULL)
			, handleManager(NULL)
			, resourceManager(NULL)
			, cameraSystem(NULL)
			, scheduler(NULL)
			, scene(NULL)
		{ }

		game::GameContextData *gameContext;

		physics::PhysicSystem *physicSystem;
		physics::Box2DPhysicSystem *box2dPhysicSystem;
		renderer::RendererSystem *rendererSystem;
		input::InputSystem *inputSystem;
		lang::HandleManager *handleManager;
		resource::ResourceManager *resourceManager;
		renderer::CameraSystem *cameraSystem;
		sys::Scheduler *scheduler;
		scene::Scene *scene;
	};

	class Context
	{
	private:
		ContextData *context;

	public:
		Context(void *context)
			: context((ContextData*)context)
		{ }

		void setContext(void *c) { context = (ContextData*)c; }//TODO: hide from user classess! 

		// Access the game context
		ContextData *getContextData() { return context; }
		game::GameContextData *getGameContext() { return context->gameContext; }

		// getters
		physics::PhysicSystem *getPhysicSystem() { assert(context->physicSystem != NULL);  return context->physicSystem; }
		physics::Box2DPhysicSystem *getBox2DPhysicSystem() { assert(context->box2dPhysicSystem != NULL);  return context->box2dPhysicSystem; }
		renderer::RendererSystem *getRendererSystem() { assert(context->rendererSystem != NULL); return context->rendererSystem; }
		input::InputSystem *getInputSystem() { assert(context->inputSystem != NULL);  return context->inputSystem; }
		lang::HandleManager *getHandleManager() { assert(context->handleManager != NULL); return context->handleManager; }
		resource::ResourceManager *getResourceManager() { assert(context->resourceManager != NULL); return context->resourceManager; }
		renderer::CameraSystem *getCameraSystem() { assert(context->cameraSystem != NULL); return context->cameraSystem; }
		sys::Scheduler *getScheduler() { assert(context->scheduler != NULL); return context->scheduler; }
		scene::Scene *getScene() { assert(context->scene != NULL); return context->scene; }

		const bool isContextValid() const { return context != NULL; }
	};

}

#endif