// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/entityeditor/EntityEditor.h"
#include "engine/GameInstance.h"
#include "editorbackend/GameEditor.h"

#include "editorbackend/CSharp/CSharpInstanceType.h"
#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "engine/scene/EntityType.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(EntityEditor);

	bool EntityEditor::init()
	{
		//registerEvents

		registerEvent("update", this, &EntityEditor::update);
		registerEvent("setTargetInstance", this, &EntityEditor::setTargetInstance);
		registerEvent("setType", this, &EntityEditor::setType);
		registerEvent("setTargetId", this, &EntityEditor::setTargetId);
		registerEvent("setTargetTypeName", this, &EntityEditor::setTargetTypeName);

		return true;
	}

	EntityEditor::~EntityEditor()
	{
		delete gameInstance;
	}

	void EntityEditor::update()
	{
		switch (type)
		{
		case EntityEditTargetType::TARGET_ENTITY:
			updateEntity();
			break;
		case EntityEditTargetType::TARGET_TYPE:
			updateType();
			break;
		}
	}

	void EntityEditor::updateEntity()
	{
		engine::component::ComponentHolder::ComponentQueue *componentRemovalQueue = entity->getComponentRemovalQueue();
		engine::component::ComponentHolder::ComponentQueue *componentAdditionQueue = entity->getComponentAdditionQueue();

		for (unsigned i = 0; i < componentAdditionQueue->size(); ++i)
		{
			unsigned id = componentAdditionQueue->at(i);
			call("addComponent", id, engine::rtti::dynamicCast<engine::component::Component>(gameInstance->getHandleManager()->getHandle(id))->getTypeInfo()->getTypeName());
		}

		componentAdditionQueue->clear();

		for (unsigned i = 0; i < componentRemovalQueue->size(); ++i)
		{
			call("removeComponent", componentRemovalQueue->at(i));
		}

		componentRemovalQueue->clear();
	}

	void EntityEditor::updateType()
	{
		if (entityType == NULL)
			return;

		if (entityType->isDirty())
		{
			// First, remove all from the UI.
			call("removeAllComponents");

			for (unsigned i = 0; i < entityType->components.size(); ++i)
			{
				call("addComponent", i, entityType->components[i].getName());
			}

			gameInstance->getEntityTypeManager()->setDirty(typeName, false);
		}
	}

	void EntityEditor::setTargetInstance(uintptr_t inst)
	{
		gameInstance = ((GameEditor*)inst)->getGameInstance();

		switch(type)
		{
		case EntityEditTargetType::TARGET_ENTITY:
			// Lets fetch the entity pointer!
			entity = engine::rtti::dynamicCast<engine::scene::Entity>(gameInstance->getHandleManager()->getHandle(targetId));

			call("setName", entity->getName());

			// If the entity has been opened before, the addition / remove queues are empty, lets trigger filling.
			entity->resetComponentQueues();

			call("setEntityType", entity->getEntityType());

			break;
		case EntityEditTargetType::TARGET_TYPE:
			entityType = gameInstance->getEntityTypeManager()->getEntityTypeByName(typeName);

			if (entityType == NULL)
			{
				LOG_ERROR("Could not find the entity type!");
				return;
			}

			gameInstance->getEntityTypeManager()->setDirty(typeName);

			call("setName", entityType->getName());

			break;
		}
	}

}