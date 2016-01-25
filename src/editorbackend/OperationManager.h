// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_OPERATIONMANAGER_H
#define EDITOR_OPERATIONMANAGER_H

#include "editorbackend/CSharp/CSharpInstance.h"

#include "editorbackend/Operation.h"
#include "engine/util/Array.h"
#include "editorbackend/entityeditor/EntityEditTargetType.h"

namespace editor {

	class OperationManager : public CSharpInstance
	{
	private:
//		engine::util::Array<Operation*> undoList;
		std::vector<Operation*> undoList;

	public:
		bool init();
		void uninit() {}

		void execute(Operation *operation);
		void revert();

		void addEmptyEntity(int64_t instance);
		void addEntity(int64_t instance, const String type, int x, int y); 
		void removeEntity(int64_t instance, unsigned entityId);

		void addComponent(int64_t instance, unsigned targetId, const String componentName); 
		void removeComponent(int64_t instance, unsigned targetId, unsigned componentId);

		void addComponentOnType(int64_t instance, const String typeName, const String componentName);
		void removeComponentOnType(int64_t instance, const String typeName, const String componentName);

		void renameEntity(int64_t instance, const unsigned targetId, const String name);

		void clear();
	};

}

#endif