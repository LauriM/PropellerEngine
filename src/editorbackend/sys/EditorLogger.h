// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_SYS_EDITORLOGGER_H
#define EDITOR_SYS_EDITORLOGGER_H

#include "engine/sys/Logger.h"

namespace editor {
namespace sys {

	class EditorLogger : public engine::sys::Logger
	{
	private:
		void *gameEditor; //Void, because the game should not know about gameeditor...

	public:
		EditorLogger(void *gameEditor);

		void error(const String &msg);
		void warning(const String &msg);
		void info(const String &msg);
	};

}
}

#endif