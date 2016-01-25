// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/editoroperations/addEmptyEntityOperation.h"
#include "editorbackend/GameEditor.h"

namespace editor {

	bool AddEmptyEntityOperation::execute()
	{
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		entityId = editor->addEmptyEntity();

		return true;
	}

	bool AddEmptyEntityOperation::revert()
	{
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		editor->removeEntityByHandleId(entityId);

		return true;
	}

}