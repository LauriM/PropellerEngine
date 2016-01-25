// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_COMPONENT_COMPONENTHOLDER_H
#define ENGINE_COMPONENT_COMPONENTHOLDER_H

#include "engine/stream/Serializable.h"

namespace engine {
namespace component {

	//Forward declarations
	PROPELLER_FORWARD_DECLARE(Component);

	class ComponentHolder : public engine::stream::Serializable
	{
	public:
		typedef std::vector<Component *> ComponentList;
		typedef std::vector<unsigned> ComponentQueue;

	private:

		DEFINE_CLASS(ComponentHolder);

		bool markedForRemoval;

	protected:
		ComponentList components;

#ifdef _EDITOR
		// Handle id's of components that have been removed
		ComponentQueue componentRemovalQueue;
		ComponentQueue componentAdditionQueue;
#endif

	public:

#ifdef _EDITOR
		ComponentQueue *getComponentRemovalQueue() { return &componentRemovalQueue; }
		ComponentQueue *getComponentAdditionQueue() { return &componentAdditionQueue; }

		void resetComponentQueues();
#endif

		ComponentHolder(void *context)
			: Serializable(context)
			, markedForRemoval(false)
		{ }

		virtual ~ComponentHolder();

		// Add component to the entity, the ptr is handled after this call
		void addComponent(Component *component);

		// Remove component from entity by ptr
		void removeComponent(Component *component);

		// Get all components
		const ComponentList & getComponents();

		// Destroy the entity and its components before the next frame
		void destroy();

		bool isMarkedForRemoval() { return markedForRemoval; }

		// Find component of specific type from the entity
		template <typename tType>
		tType* findComponent(){
			tType* output;

			for(size_t i = 0; i < components.size(); i++)
			{
				output = rtti::dynamicCast<tType>(components[i]);
				if(output != NULL)
				{
					return output;
				}
			}

			return NULL;
		}

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const {}
		void load(stream::InputStream<stream::SerializationEndian> &strm) {}

	};

} /* component */
} /* engine */

#endif /* ENGINE_COMPONENT_COMPONENTHOLDER_H */
