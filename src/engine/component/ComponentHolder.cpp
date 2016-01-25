// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/component/ComponentHolder.h"

#include "engine/component/Component.h"
#include "engine/stream/Serializable.h"
#include "engine/properties/Properties.h"

namespace engine {
namespace component {

	DECLARE_CLASS(ComponentHolder, engine::stream::Serializable);

	void ComponentHolder::destroy()
	{
		markedForRemoval = true;
	}

	ComponentHolder::~ComponentHolder() 
	{
		// First uninit, then delete

		for (unsigned i = 0; i < components.size(); ++i)
			components[i]->uninit();

		for (unsigned i = 0; i < components.size(); ++i)
			delete components[i];
	}

	void ComponentHolder::addComponent(Component *component)
	{
		component->setParent(this);
		components.push_back(component);

#ifdef _EDITOR
		componentAdditionQueue.push_back(component->getHandleId());
#endif
	}

	void ComponentHolder::removeComponent(Component *component)
	{
		for (unsigned i = 0; i < components.size(); ++i)
		{
			if (components[i] == component)
			{

				components[i]->uninit();

#ifdef _EDITOR
				componentRemovalQueue.push_back(components[i]->getHandleId());
#endif

				delete component;
				components.erase(components.begin() + i);

				return;
			}
		}

		LOG_WARNING("Could not remove the requested component!");
	}
	
#ifdef _EDITOR
	void ComponentHolder::resetComponentQueues()
	{
		componentAdditionQueue.clear();
		componentRemovalQueue.clear(); 

		for (unsigned i = 0; i < components.size(); ++i)
		{
			componentAdditionQueue.push_back(components[i]->getHandleId());
		}
	}
#endif

	const ComponentHolder::ComponentList &ComponentHolder::getComponents()
	{
		return components;
	}

} /* component */
} /* engine */
