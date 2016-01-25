// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_ENTITY_ENTITYBASE_H
#define ENGINE_ENTITY_ENTITYBASE_H

#include "engine/component/Component.h"
#include "engine/component/ComponentHolder.h"
#include "engine/stream/Serializable.h"
#include "engine/stream/InputStream.h"
#include "engine/stream/OutputStream.h"
#include "engine/util/Array.h"

namespace engine {
namespace scene {

	//TODO: SERIALIZE THE CHILDS AND PARENTS AND ALL THOSE

	class Entity : public engine::component::ComponentHolder
	{
	public:
		DEFINE_CLASS(Entity);

	private:
		String name;
		String entityType;
		bool markedForRemoval;

		// Parent entity, if NULL, its the parent
		Entity *parent;

	public:
		Entity(void *context)
			: ComponentHolder(context)
			, entityType("")
			, markedForRemoval(false)
			, parent(NULL)
#ifdef _EDITOR
			, dirty(true)
#endif
		{ }

		String &getName() { return name; }
		void setName(String newName) { name = newName; }

		void setParentEntity(Entity *p) { parent = p; }
		Entity *getParentEntity() { return parent; }

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);

		const String &getEntityType() const { return entityType; }

		// Set entity to use certain ".type". It automatically loads components relevant to the type during adding to the scene.
		void setEntityType(const String &type) { entityType = type; }

		// used by the engine to initialize all components
		void initComponents();

#ifdef _EDITOR
	private:
		bool dirty;

	public:

		bool isEntityDirty() { return dirty; }

		void setDirty(bool v) { dirty = v; }
#endif
	};


} /* namespace */
}

#endif
