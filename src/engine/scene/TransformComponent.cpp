// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/scene/TransformComponent.h"
#include "engine/math/Matrix.h"

#include "engine/scene/Entity.h"

namespace engine {
namespace scene {

	DECLARE_CLASS(TransformComponent, engine::component::Component);

	BEGIN_PROPERTIES(TransformComponent);
		DECLARE_PROPERTY(Vec3, Position);
		DECLARE_PROPERTY(Vec3, Direction);
		DECLARE_PROPERTY(float, Scale);
	END_PROPERTIES(TransformComponent);

	math::Vec3 TransformComponent::getPosition()
	{
		// Go trough parents and add transform from those to this.

		// Current entity
		Entity *ent = (Entity*)getParent();

		if (ent == NULL)
			return position;

		// Get current entities parent
		Entity *parent = ent->getParentEntity();

		if (parent == NULL)
			return position;

		TransformComponent *parentTransform = parent->findComponent<TransformComponent>();

		if (parentTransform == NULL)
			return position;

		//TODO: Add parenting to the rotation

		return parentTransform->getPosition() + position;
	}

	static math::Vec3 getPositionStatic(void *obj)
	{
		return ((TransformComponent*)obj)->getRelativePosition();
	}

	void TransformComponent::save(stream::OutputStream<stream::SerializationEndian> &strm) const
	{
		SAVE_PROPERTIES_TO_STREAM(strm);
	}

	void TransformComponent::load(stream::InputStream<stream::SerializationEndian> &strm)
	{
		LOAD_PROPERTIES_FROM_STREAM(strm, getHandleManager());
	}

}
}