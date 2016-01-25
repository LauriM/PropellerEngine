// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/CSharp/CSharpInstanceManager.h"
#include "editorbackend/CSharp/CSharpInstanceType.h"
#include "editorbackend/OperationManager.h"

//Operations
#include "editorbackend/editoroperations/addEmptyEntityOperation.h"
#include "editorbackend/editoroperations/addRemoveEntityOperation.h"
#include "editorbackend/editoroperations/addRemoveComponentOperation.h"
#include "editorbackend/editoroperations/addRemoveComponentOnTypeOperation.h"
#include "editorbackend/editoroperations/renameEntityOperation.h"

namespace editor {

	REGISTER_CSHARPINSTANCE(OperationManager);

	bool OperationManager::init()
	{
		registerEvent("revert", this, &OperationManager::revert);

		registerEvent("addEmptyEntity", this, &OperationManager::addEmptyEntity);
		registerEvent("addEntity", this, &OperationManager::addEntity);
		registerEvent("removeEntity", this, &OperationManager::removeEntity);
		registerEvent("addComponent", this, &OperationManager::addComponent);
		registerEvent("removeComponent", this, &OperationManager::removeComponent);
		registerEvent("addComponentOnType", this, &OperationManager::addComponentOnType);
		registerEvent("removeComponentOnType", this, &OperationManager::removeComponentOnType);
		registerEvent("renameEntity", this, &OperationManager::renameEntity);
		registerEvent("clear", this, &OperationManager::clear);

		return true;
	}

	void OperationManager::execute(Operation *operation)
	{
		if (operation->execute() == false)
		{
			// Operation didn't execute correctly! Bail out!
			delete operation;
			return;
		}

		undoList.push_back(operation);

		std::stringstream ss;
		ss << operation->getName();
		ss << " - ";
		ss << operation->getDesc();

		call("addUndoListEvent", ss.str());
	}

	void OperationManager::revert()
	{
		if(undoList.size() == 0)
			return;

		Operation *operation = undoList.back();
			
		undoList.pop_back();

		operation->revert();

		delete operation;

		//Update the UI
		call("revertUndoListEvent");
	}

	void OperationManager::addEmptyEntity(int64_t instance)
	{
		execute(new AddEmptyEntityOperation((CSharpInstance*)instance));
	}

	void OperationManager::addEntity(int64_t instance, const String type, int x, int y)
	{
		execute(new AddRemoveEntityOperation(AddRemoveOperationType::OPERATION_ADD, (CSharpInstance*)instance, type, x, y));
	}

	void OperationManager::removeEntity(int64_t instance, unsigned entityId)
	{
		execute(new AddRemoveEntityOperation(AddRemoveOperationType::OPERATION_REMOVE, (CSharpInstance*)instance, entityId));
	}

	void OperationManager::addComponent(int64_t instance, unsigned targetId, const String componentName)
	{
		execute(new AddRemoveComponentOperation(AddRemoveOperationType::OPERATION_ADD, (CSharpInstance*)instance, targetId, componentName));
	}

	void OperationManager::removeComponent(int64_t instance, unsigned targetId, unsigned componentId)
	{
		execute(new AddRemoveComponentOperation(AddRemoveOperationType::OPERATION_REMOVE, (CSharpInstance*)instance,targetId, componentId));
	}

	void OperationManager::addComponentOnType(int64_t instance, const String typeName, const String componentName)
	{
		execute(new AddRemoveComponentOnTypeOperation(AddRemoveOperationType::OPERATION_ADD, (CSharpInstance*)instance, typeName, componentName));
	}

	void OperationManager::removeComponentOnType(int64_t instance, const String typeName, const String componentName)
	{
		execute(new AddRemoveComponentOnTypeOperation(AddRemoveOperationType::OPERATION_REMOVE, (CSharpInstance*)instance, typeName, componentName));
	}

	void OperationManager::renameEntity(int64_t instance, const unsigned targetId, const String name)
	{
		execute(new RenameEntityOperation((CSharpInstance*)instance, targetId, name));
	}

	void OperationManager::clear()
	{
		for(unsigned i = 0; i < undoList.size(); ++i)
		{
			delete undoList[i];
		}

		undoList.clear();
	}

}