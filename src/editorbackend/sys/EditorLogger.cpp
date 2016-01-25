// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/sys/EditorLogger.h"

#include "editorbackend/GameEditor.h"

namespace editor {
namespace sys {

	EditorLogger::EditorLogger(void *gameEditor)
		: gameEditor(gameEditor)
	{}

	void EditorLogger::error(const String &msg)
	{
		((GameEditor*)gameEditor)->logError(msg);
	}

	void EditorLogger::info(const String &msg)
	{
		((GameEditor*)gameEditor)->logInfo(msg);
	}

	void EditorLogger::warning(const String &msg)
	{
		((GameEditor*)gameEditor)->logWarning(msg);
	}

}
}