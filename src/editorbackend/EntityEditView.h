// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_ENTITYEDITVIEW_H
#define EDITOR_ENTITYEDITVIEW_H

#include "engine/GameInstance.h"
#include "editorbackend/entityeditor/EntityEditTargetType.h"

namespace editor {

	// # Planning #

	//system that allows editing of "types" and "entities"
	// types would be identified with the id
	// entities would be identified with the handle id

	//Requirements
	// Add component
	// Remove component
	// Edit property
	// Edit name

	class EntityEditView
	{
	private:
		engine::GameInstance *instance;

	public:
		EntityEditView( )
			: instance(NULL)
		{ }

		void setInstance(engine::GameInstance *inst) { instance = inst; }
	};

}

#endif