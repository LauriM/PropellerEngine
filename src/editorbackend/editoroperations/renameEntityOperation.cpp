// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "editorbackend/precompiled.h"

#include "editorbackend/editoroperations/renameEntityOperation.h"
#include "editorbackend/GameEditor.h"
#include "engine/scene/Entity.h"

namespace editor {

	bool RenameEntityOperation::execute()
	{
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		engine::scene::Entity *ent = engine::rtti::dynamicCast<engine::scene::Entity>(editor->getGameInstance()->getHandleManager()->getHandle(entityId));
		oldName = ent->getName();

		editor->getGameInstance()->getScene()->renameEntity(ent, newName);

		return true;
	}

	bool RenameEntityOperation::revert()
	{
		GameEditor *editor = dynamic_cast<GameEditor*>(instance);

		engine::scene::Entity *ent = engine::rtti::dynamicCast<engine::scene::Entity>(editor->getGameInstance()->getHandleManager()->getHandle(entityId));

		editor->getGameInstance()->getScene()->renameEntity(ent, oldName);

		return true;
	}

}