// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_EDITOROPERATIONS_ADDREMOVECOMPONENTOPERATION_H
#define EDITOR_EDITOROPERATIONS_ADDREMOVECOMPONENTOPERATION_H

#include "editorbackend/Operation.h"

#include "engine/stream/BufferedOutputStream.h"
#include "editorbackend/entityeditor/EntityEditTargetType.h"
#include "engine/scene/ComponentType.h"

namespace editor {

	class AddRemoveComponentOperation : public Operation
	{
	private:
		AddRemoveOperationType opType;

		// Shared
		unsigned targetId;

		// Add
		String componentName;

		// Remove
		unsigned componentId;

		// Entity
		engine::stream::BufferedOutputStream<engine::stream::NativeEndian> componentStream;

		// Type
		engine::scene::ComponentType componentType;

	public:
		AddRemoveComponentOperation(AddRemoveOperationType opType, CSharpInstance *instance, unsigned targetId, String componentName)
			: Operation("Add Component", "Adds component to an entity", instance)
			, opType(opType)
			, targetId(targetId)
			, componentName(componentName)
		{
			if (opType != AddRemoveOperationType::OPERATION_ADD)
				LOG_ERROR("Invalid Operation type!");
		}

		AddRemoveComponentOperation(AddRemoveOperationType opType, CSharpInstance *instance, unsigned targetId, unsigned componentId)
			: Operation("Remove Component", "Removes a component from an entity", instance)
			, opType(opType)
			, targetId(targetId)
			, componentId(componentId)
		{
			if (opType != AddRemoveOperationType::OPERATION_REMOVE)
				LOG_ERROR("Invalid Operation type!");
		}

		bool execute();
		bool revert();

	private:
		bool add();
		bool remove();
	};

}

#endif