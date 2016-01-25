// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SCENE_CAMERACOMPONENT2D_H
#define ENGINE_SCENE_CAMERACOMPONENT2D_H

#include "engine/component/Component.h"
#include "engine/stream/Serializable.h"

namespace engine {
namespace scene {

	//Attach this to a camera entity.
	//Add a trackincomponent to parent the position into a another entity.
	class CameraComponent : public engine::component::Component
	{
	public:
		DEFINE_COMPONENT(CameraComponent);

		DEFINE_PROPERTY_CUSTOM_SET(bool, active, Active);

	public:
		CameraComponent(void *context);
		~CameraComponent();

		void setActive(const bool &e);

		math::Vec3 getCameraPosition();
		math::Vec3 getCameraRotation();

		//TODO: Add getRect
		//TODO: Add get frustrum

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const;
		void load(stream::InputStream<stream::SerializationEndian> &strm);
	};

}
}

#endif