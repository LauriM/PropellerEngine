// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_EDITOROPERATIONS_RENAMEENTITYOPERATION_H
#define EDITOR_EDITOROPERATIONS_RENAMEENTITYOPERATION_H

#include "editorbackend/Operation.h"

namespace editor {

	class RenameEntityOperation : public Operation
	{
	private:
		unsigned entityId;
		String oldName;
		String newName;

	public:
		RenameEntityOperation(CSharpInstance *instance, unsigned entityId, const String name)
			: Operation("Rename entity", "Renames the entitys name", instance)
			, newName(name)
			, entityId(entityId)
		{ }

		bool execute();
		bool revert();
	};

}

#endif