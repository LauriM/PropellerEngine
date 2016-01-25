// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "engine/lang/HandleManager.h"
#include "engine/scene/Entity.h"
#include "editorbackend/GameEditor.h"

#include "editorbackend/editoroperations/addRemoveComponentOperation.h"

namespace editor {

	bool AddRemoveComponentOperation::execute()
	{
		switch (opType)
		{
		case AddRemoveOperationType::OPERATION_ADD:
			return add();
		case AddRemoveOperationType::OPERATION_REMOVE:
			return remove();
		}

		return false;
	}

	bool AddRemoveComponentOperation::revert()
	{
		switch (opType)
		{
		case AddRemoveOperationType::OPERATION_ADD:
			return remove();
		case AddRemoveOperationType::OPERATION_REMOVE:
			return add();
		}

		return false;
	}

	bool AddRemoveComponentOperation::add()
	{
		GameEditor *editor = (GameEditor*)instance;

		//Find entity
		engine::scene::Entity *ent = engine::rtti::dynamicCast<engine::scene::Entity>(editor->getGameInstance()->getHandleManager()->getHandle(targetId));
		engine::component::ComponentHolder::ComponentList componentList = ent->getComponents();

		if (ent->getEntityType() != "")
		{
			LOG_WARNING("This entity is managed by a type! Add the component to type: " << ent->getEntityType());
			return false;
		}

		//Component!
		engine::component::Component *component = engine::rtti::dynamicCast<engine::component::Component>(engine::rtti::RTTI::generateSerializable(componentName, editor->getGameInstance()->getContextData()));

		engine::component::DependencyList dependencies = component->getDependencyList();

		//Check that the dependencies are avaivable...
		for (unsigned i = 0; i < dependencies.size(); ++i)
		{
			bool dependencyFound = false;

			for (unsigned x = 0; x < componentList.size(); ++x)
			{
				if (componentList[x]->getTypeInfo()->getTypeName() == dependencies[i])
				{
					dependencyFound = true;
				}
			}

			if (dependencyFound == false)
			{
				LOG_WARNING("Dependency " << dependencies[i] << " not found!");
				delete component;
				return false;
			}
		}

		// Make sure there aren't any duplicates of the component
		for (unsigned i = 0; i < componentList.size(); ++i)
		{
			if (componentList[i]->getTypeInfo()->getTypeName() == componentName)
			{
				LOG_WARNING("The entity already has " << componentName << " as component!");
				delete component;
				return false;
			}
		}

		if (opType == OPERATION_REMOVE)
		{
			//Its a revert! Load the data from the stream
			component->load(engine::stream::InputStream<engine::stream::NativeEndian>((volatile void*)componentStream.getData()));
		}

		componentId = component->getHandleId();

		ent->addComponent(component);

		editor->getGameInstance()->refreshEntity(ent);

		return true;
	}

	bool AddRemoveComponentOperation::remove()
	{
		GameEditor *editor = (GameEditor*)instance;

		engine::scene::Entity *ent = engine::rtti::dynamicCast<engine::scene::Entity>(editor->getGameInstance()->getHandleManager()->getHandle(targetId));

		if (ent->getEntityType() != "")
		{
			LOG_WARNING("This entity is managed by a type! Remove the component in type: " << ent->getEntityType());
			return false;
		}

		engine::component::ComponentHolder::ComponentList componentList = ent->getComponents();

		engine::component::Component *component = engine::rtti::dynamicCast<engine::component::Component>(editor->getGameInstance()->getHandleManager()->getHandle(componentId));

		//Check if any other component requires the one to be removed.
		for (unsigned i = 0; i < componentList.size(); ++i)
		{
			engine::component::DependencyList dependencies = componentList[i]->getDependencyList();

			for (unsigned x = 0; x < dependencies.size(); ++x)
			{
				if (dependencies[x] == component->getTypeInfo()->getTypeName())
				{
					//Found dependency!
					LOG_WARNING("Cannot remove component because " << componentList[i]->getTypeInfo()->getTypeName() << " requires it!");
					return false;
				}
			}
		}

		componentName = component->getTypeInfo()->getTypeName();

		component->save(componentStream);

		ent->removeComponent(component);

		return true;
	}

}