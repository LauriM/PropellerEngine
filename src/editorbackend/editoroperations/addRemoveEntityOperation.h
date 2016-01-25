// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_EDITOROPERATIONS_ADDREMOVEENTITYOPERATION_H
#define EDITOR_EDITOROPERATIONS_ADDREMOVEENTITYOPERATION_H

#include "editorbackend/Operation.h"

#include "engine/stream/BufferedOutputStream.h"

namespace editor {

	class AddRemoveEntityOperation : public Operation
	{
	private:
		// Operation info
		AddRemoveOperationType opType;

		// Needed for execute
		String type;
		int x;
		int y;

		// Needed for revert
		unsigned entityId;

		engine::stream::BufferedOutputStream<engine::stream::NativeEndian> entityStream;

	public:
		AddRemoveEntityOperation(AddRemoveOperationType opType, CSharpInstance *instance, String type, int x, int y)
			: Operation("Add Entity", "Adds entity based on prefab to the scene.", instance)
			, opType(opType)
			, type(type)
			, x(x)
			, y(y)
		{ 
			if(opType != OPERATION_ADD)
				LOG_ERROR("Wrong AddRemoveOperationType!");
		}

		AddRemoveEntityOperation(AddRemoveOperationType opType, CSharpInstance *instance, unsigned entityId)
			: Operation("Remove Entity", "Removes entity from the scene", instance)
			, opType(opType)
			, entityId(entityId)
		{
			if(opType != OPERATION_REMOVE)
				LOG_ERROR("Wrong AddRemoveOperationType!");
		}

		bool execute();
		bool revert();

	private:
		bool insert();
		bool remove();
	};

}

#endif