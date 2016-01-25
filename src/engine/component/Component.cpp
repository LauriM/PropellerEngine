// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/component/Component.h"
#include "engine/component/ComponentHolder.h"

#include "engine/properties/Properties.h"
#include "engine/stream/OutputStream.h"
#include "engine/stream/InputStream.h"
#include "engine/stream/Serializable.h"
#include "engine/rtti/RTTI.h"

namespace engine {
namespace component {

	DECLARE_ABSTRACT_CLASS(Component, engine::stream::Serializable);

	Component::Component(void *context)
		: Serializable(context)
	{ }

	ComponentHolder* Component::getParent()
	{
		return this->parent;
	}

	void Component::setParent(ComponentHolder *parent)
	{
		this->parent = parent;
	}

}
}
