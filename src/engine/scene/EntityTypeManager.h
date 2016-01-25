// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_ENTITYTYPESYSTEM_H
#define ENGINE_SCENE_ENTITYTYPESYSTEM_H

#include "engine/file/FileManager.h"
#include "engine/scene/EntityType.h"
#include "engine/Context.h"

PROPELLER_FORWARD_DECLARE_2(engine, scene, Entity);
PROPELLER_FORWARD_DECLARE_2(engine, component, Component);

namespace engine {
namespace scene {

	// EngineTypeSystem manages, loads and handles all EtityTypes.
	class EntityTypeManager
	{
	public:
		typedef std::vector<EntityType> EntityTypeVector;

	private:
		ContextData *context;
		file::FileManager *fileManager;

		EntityTypeVector entityTypes;

	public:
		EntityTypeManager()
			: fileManager(NULL)
			, context(NULL)
		{ }

		EntityTypeManager(file::FileManager *fileManager, ContextData *context)
			: fileManager(fileManager)
			, context(context)
		{
			reloadAllTypesFromDisk();
		}

	public:
		const EntityTypeVector &getEntityTypeVector() const { return entityTypes; }

		const EntityType *getEntityTypeByName(const String &name) const;

#ifdef _EDITOR
		void setDirty(const String &name);
		void setDirty(const String &name, bool dirt);

		void saveTypesToDisk();
#endif

		void applyTypeOnEntity(Entity *ent);
		void applyTypeOnComponent(const ComponentType &type, component::Component *component);

		// Methods to modify the types
		bool addComponent(const String &typeName, const String &componentName);
		bool addComponent(EntityType *type, const String &componentName);

		bool removeComponent(const String &typeName, const String &componentName);
		bool removeComponent(EntityType *type, const String &componentName);

		void createNewEntityType(const String &name);

	private:
		void reloadAllTypesFromDisk();

		EntityType *getEntityTypePtrByName(const String &name);

	};

}
}

#endif
