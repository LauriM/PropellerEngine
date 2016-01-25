// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/scene/Scene.h"
#include "engine/rtti/RTTI.h"

namespace engine {
namespace scene {

	DECLARE_ABSTRACT_CLASS(Scene, engine::stream::Serializable);

	void Scene::addEntity(Entity *entity)
	{
		//Lets add the entity to the handlelist also

		entities.push_back(entity);

		entity->initComponents();

#ifdef _EDITOR
		entity->setDirty(true);
		entityListDirty = true;
#endif
	}

	// Remove entity by handle ID
	void Scene::removeEntityById(unsigned handle)
	{
		Entity *ent = engine::rtti::dynamicCast<Entity>(getHandleManager()->getHandle(handle));

		removeEntity(ent);
	}

	void Scene::removeEntity(Entity *entity)
	{
		for (unsigned i = 0; i < entities.size(); ++i)
		{
			if (entities[i] == entity)
			{
				removeEntityByIndex(i);
				return;
			}
		}
	}

	void Scene::removeEntityByIndex(unsigned i)
	{
		unsigned handle = entities[i]->getHandleId();

		delete entities[i];
		entities.erase(entities.begin() + i);
#ifdef _EDITOR
		//Entity list marked dirty for the update to trigger
		entityListDirty = true;

		//Update the list of removed handles
		removedHandles.push_back(handle);
#endif
	}

	// Rename entity and add it to the list of for UI refresh
	void Scene::renameEntity(Entity *ent, const String &name)
	{
		ent->setName(name);


#ifdef _EDITOR
		renamedHandles.push_back(ent->getHandleId());
		entityListDirty = true;
#endif
	}

	Scene::~Scene()
	{
		for(unsigned i = 0; i < entities.size(); ++i)
			removeEntity(entities[i]);
	}

	void Scene::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		PROFILE;
		strm.write(ENGINE_VERSION_MAJOR);
		strm.write(ENGINE_VERSION_MINOR);
		strm.write(ENGINE_VERSION_PATCH);

		strm.write(entities.size());

		for (unsigned i = 0; i < entities.size(); ++i)
		{
			entities[i]->save(strm);
		}
	}

	void Scene::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		PROFILE;
		int engineMajor, engineMinor, enginePatch;

		strm.read(engineMajor);
		strm.read(engineMinor);
		strm.read(enginePatch);

		if (engineMajor != ENGINE_VERSION_MAJOR || engineMinor != ENGINE_VERSION_MINOR || enginePatch != ENGINE_VERSION_PATCH)
		{
			LOG_ERROR("Invalid version number on scene file, aborting load. Engine: " << ENGINE_VERSION_MAJOR << "." << ENGINE_VERSION_MINOR << "." << ENGINE_VERSION_PATCH << " File: " << engineMajor << "." << engineMinor << "." << enginePatch);
			return;
		}

		//Loading happens in two steps.
		//a) build the scene data as it is in the stream
		//b) Refresh Handle pointers
		//c) Refresh resources

		unsigned entityCount;

		strm.read(entityCount);

		for (unsigned i = 0; i < entityCount; ++i)
		{
			Entity *ent = rtti::dynamicCast<Entity>(rtti::RTTI::generateSerializable("Entity", getContextData()));

			ent->load(strm);

			entities.push_back(ent);
		}
	}

	void Scene::cleanRemovedEntities()
	{
		PROFILE;

		//TODO: this could be optimized with a queue
		for (unsigned i = 0; i < entities.size(); ++i)
		{
			if (entities[i]->isMarkedForRemoval())
			{
				removeEntityByIndex(i);

				//one entity removed, move i back,
				--i;
			}
		}

	}

	void Scene::resetScene()
	{
		for (unsigned i = 0; i < entities.size(); ++i)
			delete entities[i];

		entities.clear();
	}

}
}