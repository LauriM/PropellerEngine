// Copyright (c) Lauri Mäkinen 2014
// All rights reserved.
#ifndef EDITOR_ENTITYEDITVIEW_H
#define EDITOR_ENTITYEDITVIEW_H

#include "game/GameInstance.h"
#include "editorbackend/EntityEditTargetType.h"

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
		GameInstance *instance;

	public:
		EntityEditView( )
			: instance(NULL)
		{ }

		void setInstance(GameInstance *inst) { instance = inst; }

		void addComponent(unsigned id, String componentName, EntityEditTargetType targetType);

		void requestComponentList(unsigned id, EntityEditTargetType targetType, std::vector<String> *output);
	};

}

#endif