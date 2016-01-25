// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_MODELVIEWER_H
#define EDITOR_MODELVIEWER_H

#include "editorbackend/CSharp/CSharpInstance.h"

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);
PROPELLER_FORWARD_DECLARE_2(engine, scene, Entity);

namespace editor {

	class ModelViewer : public CSharpInstance
	{
	private:
		engine::GameInstance *instance;

		// the one and only entity thats used to view the models
		engine::scene::Entity *entity;

	public:
		bool init();
		void uninit();
		void update();

		void keyUp(int keyCode);
		void keyDown(int keyCode);
		void mouseDeltaInput(float x, float y);

		void initModelViewer(String modelName, intptr_t hwnd);

		void toggleWireframe();
		void toggleGrid();
	};

}

#endif