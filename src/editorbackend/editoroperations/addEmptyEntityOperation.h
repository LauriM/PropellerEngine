// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_OPERATIONS_ADDEMPTYENTITYOPERATION_H
#define EDITOR_OPERATIONS_ADDEMPTYENTITYOPERATION_H

#include "editorbackend/Operation.h"

namespace editor {

	class AddEmptyEntityOperation : public Operation
	{
	private:
		unsigned entityId;

	public:
		AddEmptyEntityOperation(CSharpInstance *instance)
			: Operation("Add empty entity", "Creates an entity without components.", instance)
			, entityId(0)
		{ }

		bool execute();
		bool revert();
	};

}

#endif