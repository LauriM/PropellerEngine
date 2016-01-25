// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_PARTICLEDITOR_H
#define EDITOR_PARTICLEDITOR_H

#include "editorbackend/CSharp/CSharpInstance.h"

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);

namespace editor {

	class ParticleEditor : public CSharpInstance
	{
	private:
		engine::GameInstance *instance;

	public:
		bool init();
		void uninit();
		void update();

		void initRender(intptr_t hwnd);
	};

}

#endif