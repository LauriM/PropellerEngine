// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"
#include "editorbackend/EntityEditView.h"
#include "engine/scene/Entity.h"
#include "editorbackend/entityeditor/EntityEditTargetType.h"

namespace editor {

	/*
	void EntityEditView::requestComponentList(unsigned id, EntityEditTargetType targetType, std::vector<String> *output)
	{
		engine::component::ComponentHolder::ComponentList componentList;
		engine::scene::Entity *ent;

		switch(targetType)
		{
		case EntityEditTargetType::TARGET_ENTITY:
			ent = engine::rtti::dynamicCast<engine::scene::Entity>(engine::lang::getHandleManager()->getHandle(id));

			componentList = ent->getComponents();

			for(unsigned i = 0; i < componentList.size(); ++i)
				output->push_back(componentList[i]->getTypeInfo()->getTypeName());

			break;
		default:
			break;
		}
	}
	*/

}