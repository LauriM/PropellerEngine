// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef EDITOR_ENTITYEDITOR_ENTITYEDITOR_H
#define EDITOR_ENTITYEDITOR_ENTITYEDITOR_H

#include "editorbackend/CSharp/CSharpInstance.h"
#include "editorbackend/entityeditor/EntityEditTargetType.h"

PROPELLER_FORWARD_DECLARE_1(engine, GameInstance);
PROPELLER_FORWARD_DECLARE_2(engine, scene, Entity);
PROPELLER_FORWARD_DECLARE_2(engine, scene, EntityType);

namespace editor {

	class EntityEditor : public CSharpInstance
	{
	private:
		engine::GameInstance *gameInstance;

		unsigned targetId;
		EntityEditTargetType type;

		// Either a pointer to the entity in the scene, or own personal entity for display.

		// TYPE_ENTITY
		engine::scene::Entity *entity;

		// TYPE_TYPE
		String typeName;
		const engine::scene::EntityType *entityType;

	public:
		EntityEditor()
			: gameInstance(NULL)
		{ }

		~EntityEditor();

		bool init();
		void uninit() { }

		// Sets targets instance where the entity information should be updated.
		void setType(unsigned t) { type = EntityEditTargetType(t); }
		void setTargetId(unsigned id) { targetId = id; }
		void setTargetTypeName(String file) { typeName = file; }
		void setTargetInstance(uintptr_t gameInstance);

		// Checks the dirty flags and updates the UI.
		void update();

	private:
		void updateEntity();
		void updateType();

	};

}

#endif