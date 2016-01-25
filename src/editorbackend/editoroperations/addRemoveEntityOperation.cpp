// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/editoroperations/addRemoveEntityOperation.h"
#include "editorbackend/GameEditor.h"
#include "engine/scene/Entity.h"
#include "engine/stream/InputStream.h"

namespace editor {

	bool AddRemoveEntityOperation::execute()
	{
		switch(opType)
		{
		case AddRemoveOperationType::OPERATION_ADD:
			return insert();
		case AddRemoveOperationType::OPERATION_REMOVE:
			return remove();
		}

		return false;
	}

	bool AddRemoveEntityOperation::revert()
	{
		switch(opType)
		{
		case AddRemoveOperationType::OPERATION_ADD:
			return remove();
		case AddRemoveOperationType::OPERATION_REMOVE:
			return insert();
		}

		return false;
	}

	bool AddRemoveEntityOperation::insert()
	{
		//Get the editor from the instance
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		if (editor == NULL)
		{
			LOG_ERROR("Invalid instance type during execution!");
			return false;
		}


		switch(opType)
		{
		case AddRemoveOperationType::OPERATION_ADD:
			// its add, just regular insert
			entityId = editor->addEntityByType(type, x, y);
			return true;
		case AddRemoveOperationType::OPERATION_REMOVE:
			// Its remove before! Should be inserted from a stream
			scene::Entity *ent = rtti::dynamicCast<scene::Entity>(rtti::RTTI::generateSerializable("Entity", editor->getGameInstance()->getContextData()));

			ent->load(engine::stream::InputStream<engine::stream::NativeEndian>((volatile void*)entityStream.getData()));

			editor->getGameInstance()->getScene()->addEntity(ent);

			editor->getGameInstance()->refreshEntityId(ent->getHandleId());

			return true;
		}

		return false;
	}

	bool AddRemoveEntityOperation::remove()
	{
		//Get the editor from the instance
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		if (editor == NULL)
		{
			LOG_ERROR("Invalid instance type during revert!"); 
			return false;
		}

		switch(opType)
		{
		case AddRemoveOperationType::OPERATION_ADD:
			// Just added entity can be removed without stream saving.
			editor->removeEntityByHandleId(entityId);
			return true;
		case AddRemoveOperationType::OPERATION_REMOVE:
			// Its just a pure remove, we need to take copy of the entity to the memory.
			engine::scene::Entity *ent = engine::rtti::dynamicCast<engine::scene::Entity>(editor->getGameInstance()->getHandleManager()->getHandle(entityId));

			ent->save(entityStream);

			editor->removeEntityByHandleId(entityId);
			return true;
		}

		return false;
	}

}