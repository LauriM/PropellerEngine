// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_SCENE_H
#define ENGINE_SCENE_SCENE_H

#include "engine/stream/Serializable.h"
#include "engine/stream/InputStream.h"
#include "engine/stream/OutputStream.h"
#include "engine/scene/Entity.h"
#include "engine/lang/HandleManager.h"

namespace engine {
namespace scene {

	class Scene : public engine::stream::Serializable
	{
	public:
		DEFINE_CLASS(Scene);

		typedef std::vector< Entity* > EntityList;

	protected:
		EntityList entities;

#ifdef _EDITOR
		// If there is somethign to add,remove or rename on the list.
		bool entityListDirty;

	public:
		typedef std::vector<unsigned> RemovedHandleList;
		typedef std::vector<unsigned> RenamedHandleList;

	private:
		RemovedHandleList removedHandles;
		RenamedHandleList renamedHandles;
#endif

	public:
		Scene(void *context)
			: Serializable(context)
		{ }

		~Scene();

		// Add an entity to the scene, the ptr is handled by the scene after this
		void addEntity(Entity *entity);

		// Remove entity by its pointer
		void removeEntity(Entity *entity);

		// Remove entity by its handle id
		void removeEntityById(unsigned handle);

		// Rename entity given the ptr and new name
		void renameEntity(Entity *ent, const String &name);

		// Get static reference to a list of all entities
		const EntityList* getEntityList() const
		{
			return &entities;
		}

		// Get pointer to list of all entities
		EntityList* getEntities()
		{
			return &entities;
		}

#ifdef _EDITOR
		//Is entity list dirty? If so, reset the flag as the editor should update the list.
		bool isEntityListDirty()
		{
			if (entityListDirty == true)
			{
				entityListDirty = false;
				return true;
			}

			return false;
		}

		void markEntityListDirty()
		{
			entityListDirty = true;
		}

		const RemovedHandleList &getRemovedHandleList() const
		{
			return removedHandles;
		}

		const RenamedHandleList &getRenamedHandleList() const
		{
			return renamedHandles;
		}

		void clearRemovedHandles()
		{
			removedHandles.clear();
		}

		void clearRenamedHandles()
		{
			renamedHandles.clear();
		}
#endif

		// Clean entities that have been marked for removal, called by the engine
		void cleanRemovedEntities();

		// Remove all entities and components from the active scene
		void resetScene();
		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);

	private:
		void removeEntityByIndex(unsigned i);
	};

}
}

#endif
