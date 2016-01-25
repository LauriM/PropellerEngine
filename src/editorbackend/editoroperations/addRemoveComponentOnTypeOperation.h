// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_EDITOROPERATIONS_ADDREMOVECOMPONENTONTYPEOPERATION_H
#define ENGINE_EDITOROPERATIONS_ADDREMOVECOMPONENTONTYPEOPERATION_H

#include "editorbackend/Operation.h"

#include "editorbackend/entityeditor/EntityEditTargetType.h"

namespace editor {

	class AddRemoveComponentOnTypeOperation : public Operation
	{
	private:
		AddRemoveOperationType opType;

		// Shared
		String targetTypeName;

		// Addition
		String componentName;

	public:
		AddRemoveComponentOnTypeOperation(AddRemoveOperationType opType, CSharpInstance *instance, const String &targetTypeName, const String &componentName)
			: Operation("Add component to type", "Adds component to a type", instance)
			, opType(opType)
			, targetTypeName(targetTypeName)
			, componentName(componentName)
		{}

		//AddRemoveComponentOnTypeOperation(AddRemoveOperationType opType, CSharpInstance *instance, String targetTypeName, String componentName)

		bool execute();
		bool revert();

	private:
		bool add();
		bool remove();
	};

}

#endif