// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_ENTITYTYPE_H
#define ENGINE_SCENE_ENTITYTYPE_H

#include "engine/file/FileData.h"

#include "engine/scene/ComponentType.h"

namespace engine {
namespace scene {

	// Single entity
	class EntityType
	{
	private:
		String name;

#ifdef _EDITOR
		bool dirty;
		bool syncedWithDisk;
#endif

	public:
		EntityType()
			: name("nullType")
#ifdef _EDITOR
			, dirty(true)
			, syncedWithDisk(true)
#endif
		{ }

		typedef std::vector<ComponentType> ComponentTypeList;

		ComponentTypeList components;

		const String &getName() const { return name; }

		void setName(String n) { name = n; }

		String saveToJson() const;
		void loadFromJson(const String &str);

		void loadFromFile(file::File file);

#ifdef _EDITOR
		// Used in entityEditor.
		bool isDirty() const { return dirty; }
		void setDirty(const bool d) { dirty = d; }

		bool isSyncedWithDisk() const { return syncedWithDisk; }
		void setSyncedWithDisk(const bool s) { syncedWithDisk = s; }
#endif
	};

}
}

#endif