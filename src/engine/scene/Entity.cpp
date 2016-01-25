// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/scene/Entity.h"

#include "engine/component/ComponentHolder.h"

namespace engine {
namespace scene {

	DECLARE_CLASS(Entity, engine::component::ComponentHolder);

	void Entity::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		strm.write(name);
		strm.write(entityType);

		//Other data is inside the components, loop trough them and save them

		strm.write(components.size());
		for (unsigned i = 0; i < components.size(); ++i)
		{
			//Type to create
			strm.write(components[i]->getTypeInfo()->getTypeName());
			//What the component actually has in it
			components[i]->save(strm);
		}
	}

	void Entity::initComponents()
	{
		for (unsigned i = 0; i < components.size(); ++i)
			components[i]->init();
	}

	void Entity::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		if (!isContextValid())
		{
			LOG_ERROR("Trying to load entity! CONTEXT NOT SET! ABORTING!");
			return;
		}

		strm.read(name);
		strm.read(entityType);

		unsigned compCount;

		strm.read(compCount);

		for (unsigned i = 0; i < compCount; ++i)
		{
			String typeName;
			strm.read(typeName);

			component::Component *comp = engine::rtti::dynamicCast<component::Component>(rtti::RTTI::generateSerializable(typeName, getContextData()));

			comp->load(strm);

			this->addComponent(comp);
		}

		// call the init()'s on the components after the load
		for (unsigned i = 0; i < components.size(); ++i)
			components[i]->init();
	}

}
}