// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYSTEMBASE_H
#define ENGINE_SYSTEMBASE_H

PROPELLER_FORWARD_DECLARE_2(engine, component, Component);

namespace engine {

	class SystemBase
	{
	private:

#ifdef _EDITOR
		double timing; //TODO: This is deprecrated and no longer in use, should be removed
#endif

		// Execution order weight
		int weight;

		bool running;

	protected:
		std::vector<component::Component*> components;

	public:
		virtual ~SystemBase() {};

		virtual bool init() = 0;
		virtual void uninit() = 0;
		virtual void update(float delta) = 0;

		virtual const String getName() = 0;

		// Does the system have effect gameplay? (aka, can it be run during editor?)
		// By default true, override and set to false if you want the system to update during editor actions
		virtual const bool isGameplaySystem() { return true; }
		virtual const bool isRendererSystem() { return false; }
		//TODO: the virtuality can be removed here

		// Set the weight of the system, this sets the order where the engine runs the systems. Higher weigt, later the system is run
		void setWeight(int w) { weight = w; }
		const int getWeight() const { return weight; }

		// Used to register components to the system
		void addComponent(component::Component *component);

		// Used to unreigster components from the system
		void removeComponent(component::Component *component);

		bool isRunning() const { return running; }
		void stop() { running = false; }
		void start() { running = true; }

#ifdef _EDITOR
		const double getTiming() const { return double(0); }//TODO: This is deprecrated and no longer in use, should be removed
#endif
	};

}

#endif
