// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/GameEditor.h"
#include "editorbackend/editoroperations/addRemoveComponentOnTypeOperation.h"

namespace editor {

	bool AddRemoveComponentOnTypeOperation::execute()
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

	bool AddRemoveComponentOnTypeOperation::revert()
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

	bool AddRemoveComponentOnTypeOperation::add()
	{
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		if (editor->getGameInstance()->getEntityTypeManager()->addComponent(targetTypeName, componentName))
		{
			editor->getGameInstance()->reloadTypeData();

			return true;
		}


		return false;
	}

	bool AddRemoveComponentOnTypeOperation::remove()
	{
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		if (editor->getGameInstance()->getEntityTypeManager()->removeComponent(targetTypeName, componentName))
		{
			editor->getGameInstance()->reloadTypeData();

			return true;
		}

		return false;
	}

}
