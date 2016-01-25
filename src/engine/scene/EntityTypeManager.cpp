// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/scene/EntityTypeManager.h"

#include "engine/scene/Entity.h"
#include "engine/component/ComponentHolder.h"
#include "engine/scene/ComponentType.h"
#include "engine/properties/Properties.h"
#include "engine/sys/FileSystem.h"
#include "engine/console/Cvar.h"

#ifdef _EDITOR
namespace cvar {
	CVAR(String, devdatapath, "./../data/", false);
}
#endif

namespace engine {
namespace scene {

	void EntityTypeManager::reloadAllTypesFromDisk()
	{
		PROFILE;

		if (fileManager == NULL)
		{
			LOG_ERROR("[EntityTypeManager] fileManager is NULL!");
			return;
		}

		entityTypes.clear(); //the data will be fresh from the disk

		//Query all folders with types (.type)
		int counter = 0;

		file::FileList fileList;
		fileManager->listFiles(fileList);

		for (unsigned i = 0; i < fileList.getSize(); ++i)
		{
			String fileStr = fileList[i];

			if (fileStr.substr(fileStr.find_last_of(".") + 1) == "type")
			{
				EntityType type;
				type.loadFromFile(fileManager->openFile(fileStr));
				type.setName(fileStr);

				entityTypes.push_back(type);
				++counter;
			}
		}

		LOG_INFO("[EntityTypeManager] Loaded " << counter << " types.");
	}

	const EntityType *EntityTypeManager::getEntityTypeByName(const String &name) const
	{
		PROFILE;

		for (unsigned i = 0; i < entityTypes.size(); ++i)
		{
			if (entityTypes[i].getName() == name)
			{ 
				return &entityTypes[i];
			}
		}

		LOG_ERROR("Could not find entity type specified!");
		return NULL;
	}

	EntityType *EntityTypeManager::getEntityTypePtrByName(const String &name)
	{
		PROFILE;

		for (unsigned i = 0; i < entityTypes.size(); ++i)
		{
			if (entityTypes[i].getName() == name)
			{
				return &entityTypes[i];
			}
		}

		LOG_ERROR("Could not find entity type specified!");
		return NULL;
	}


#ifdef _EDITOR
	// Set dirty to true
	void EntityTypeManager::setDirty(const String &name)
	{
		setDirty(name, true);
	}

	void EntityTypeManager::setDirty(const String &name, bool dirt)
	{
		for (unsigned i = 0; i < entityTypes.size(); ++i)
		{
			if (entityTypes[i].getName() == name)
			{
				entityTypes[i].setDirty(dirt);
			}
		}
	}
#endif

	//Applies type into entity, uses the id in the entity, NOTE: remember to refresh the entity!
	//Removes / Adds components
	void EntityTypeManager::applyTypeOnEntity(Entity *ent)
	{
		PROFILE;
		if (ent->getEntityType() == "")
			return; 

		const EntityType *type = getEntityTypeByName(ent->getEntityType());

		if (type == NULL)
			return; // The type doesn't exists

		if(ent->getName().empty())
		{
			ent->setName(type->getName());
		}

		// Applying type to entity works in following way
		//
		// Loop
		//     Check if new components should be added
		//     Check if old components should have changes
		// Loop (reverse)
		//     Check if components should be removed

		component::ComponentHolder::ComponentList componentList = ent->getComponents();


		for(unsigned x = 0; x < type->components.size(); ++x)
		{
			bool found = false;

			for(unsigned i = 0; i < componentList.size(); ++i)
			{
				if(type->components[x].getName() == componentList[i]->getTypeInfo()->getTypeName())
				{
					ComponentType compType = type->components[x];
					applyTypeOnComponent(compType, componentList[i]);
					found = true;
				}
			}

			if(found == false)
			{
				// The component in the type was not found, add it.

				ComponentType compType = type->components[x];

				stream::Serializable *comp = rtti::RTTI::generateSerializable(compType.getName(), context);

				component::Component *component = rtti::dynamicCast<engine::component::Component>(comp);

				applyTypeOnComponent(compType, component);

				ent->addComponent(component);
			}
		}

		component::ComponentHolder::ComponentList componentRemovalQueue;

		// Remove old components not present in the type
		for (unsigned i = 0; i < componentList.size(); ++i)
		{
			bool found = false;
			for (unsigned x = 0; x < type->components.size(); ++x)
			{
				if (type->components[x].getName() == componentList[i]->getTypeInfo()->getTypeName())
					found = true; continue;
			}

			if (found == false)
			{
				// Could not found the component in the type! It should be removed.
				componentRemovalQueue.push_back(componentList[i]);
			}
		}

		//Remove components in the queue
		for (unsigned i = 0; i < componentRemovalQueue.size(); ++i)
		{
			ent->removeComponent(componentRemovalQueue[i]);
		}
	}

	void EntityTypeManager::applyTypeOnComponent(const ComponentType &type, component::Component *component)
	{
		PROFILE;
		// Loop trough properties in types, apply into the component

		const PropertyTypeVector typeProperties = type.getPropertyTypeVector();
		properties::PropertyVector componentProperties = component->getProperties();

		for(unsigned i = 0; i < typeProperties.size(); ++i)
		{
			for(unsigned x = 0; x < componentProperties.size(); ++x)
			{
				if(typeProperties[i].name == componentProperties[x].getName())
				{
					switch(typeProperties[i].type)
					{
					default:
						DEBUG_PRINT("NOT IMPLEMENTED!");
						DEBUG_BREAK;
						break;
					case properties::PropertyTypeUnsigned:
						componentProperties[x].set(component, typeProperties[i].value.valueUnsigned);
						break;
					case properties::PropertyTypeSigned:
						componentProperties[x].set(component, typeProperties[i].value.valueSigned);
						break;
					case properties::PropertyTypeBool:
						componentProperties[x].set(component, typeProperties[i].value.valueBool);
						break;
					case properties::PropertyTypeFloat:
						componentProperties[x].set(component, typeProperties[i].value.valueFloat);
						break;
					case properties::PropertyTypeDouble:
						componentProperties[x].set(component, typeProperties[i].value.valueDouble);
						break;
					case properties::PropertyTypeString:
						componentProperties[x].set(component, typeProperties[i].valueString);
						break;
					case properties::PropertyTypeVec2:
						DEBUG_BREAK; //TODO: Vec2 not yet implemented for json serialization!
						break;
					}
				}

			}
		}
	}

	bool EntityTypeManager::addComponent(const String &typeName, const String &componentName)
	{
		return addComponent(getEntityTypePtrByName(typeName), componentName);
	}

	bool EntityTypeManager::addComponent(EntityType *type, const String &componentName)
	{
		engine::scene::EntityType::ComponentTypeList components = type->components;

#ifdef _EDITOR
		engine::component::Component *tempComponent = engine::rtti::dynamicCast<engine::component::Component>(engine::rtti::RTTI::generateSerializable(componentName, context));
		engine::component::DependencyList dependencies = tempComponent->getDependencyList();
		delete tempComponent;

		for (unsigned x = 0; x < dependencies.size(); ++x)
		{
			bool found = false;

			for (unsigned i = 0; i < components.size(); ++i)
			{
				if (components[i].getName() == dependencies[x])
					found = true;
			}

			if (found == false)
			{
				LOG_WARNING("Dependency " << dependencies[x] << " not found! Not adding.");
				return false;
			}
		}
#endif

		for (unsigned i = 0; i < components.size(); ++i)
		{
			if (components[i].getName() == componentName)
			{
				LOG_WARNING("The component already exists! Not adding.");
				return false;
			}
		}

		// Checks ok, add the component
		type->components.push_back(engine::scene::ComponentType(componentName));
		// TODO: IMPLEMENT THE RESTORATION OF THE OLD TYPE!

#ifdef _EDITOR
		type->setDirty(true);
		type->setSyncedWithDisk(false);
#endif
		return true;
	}

	bool EntityTypeManager::removeComponent(const String &typeName, const String &componentName)
	{
		engine::scene::EntityType *type = getEntityTypePtrByName(typeName);

		const engine::scene::EntityType::ComponentTypeList componentList = type->components;

		unsigned componentId = 0;

		for (unsigned i = 0; i < componentList.size(); ++i)
		{
#ifdef _EDITOR
			LOG_WARNING("Dependency check disabled due to potential error! (TODO, Fix it)");
			/*
			//Create a temporary component to get the dependency list.
			engine::component::Component *component = engine::rtti::dynamicCast<engine::component::Component>(engine::rtti::RTTI::generateSerializable(componentList[i].getName(), context));
			engine::component::DependencyList dependencies = component->getDependencyList(); //TODO: wtf, fix this
			delete component; //HACK

			for (unsigned x = 0; x < dependencies.size(); ++x)
			{
				if (dependencies[x] == componentName)
				{
					//Found dependency!
					LOG_WARNING("Cannot remove component because " << componentList[i].getName() << " requires it!");
					return false;
				}
			}
			*/
#endif

			if (componentList[i].getName() == componentName)
				componentId = i;
		}

		// Removing should be ok, do it!

		// componentId represents the position in the list (! List needs to be recreated for the following removals to be correct)

		//TODO: cleanup
		type->components.erase(type->components.begin() + componentId);

#ifdef _EDITOR
		type->setDirty(true);
		type->setSyncedWithDisk(false);
#endif

		return true;
	}

	bool EntityTypeManager::removeComponent(EntityType *entity, const String &componentName)
	{
		/*not impl*/
		LOG_ERROR("Not implemented! (removeComponent");
		return false;
	}

#ifdef _EDITOR

	// Saves unsynced types to disk.
	void EntityTypeManager::saveTypesToDisk()
	{
		for (unsigned i = 0; i < entityTypes.size(); ++i)
		{
			if (entityTypes[i].isSyncedWithDisk() == false)
			{
				std::stringstream ss;
				ss << cvar::devdatapath.get();
				ss << entityTypes[i].getName();
				String filename = ss.str();

				FILE *file = fopen(filename.c_str(), "w");

				if (file == NULL)
				{
					LOG_ERROR("Failed to write entitytype " << filename);
					continue;
				}

				fputs(entityTypes[i].saveToJson().c_str(), file);

				fclose(file);

				entityTypes[i].setSyncedWithDisk(true);

				LOG_INFO("EntityType " << filename << " saved.");
			}
		}
	}

#endif

	void EntityTypeManager::createNewEntityType(const String &name)
	{
		EntityType type;

		type.setName(name);

#ifdef _EDITOR
		type.setDirty(true); //dirty by default so it gets saved
		type.setSyncedWithDisk(false);
#endif

		entityTypes.push_back(type);

		LOG_INFO("[EntityTypeManager] Created entityType " << name);
	}

}
}
