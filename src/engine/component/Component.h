// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef Component_H
#define Component_H

#include "engine/stream/Serializable.h"
#include "engine/properties/Properties.h"
#include "engine/component/Dependencies.h"

PROPELLER_FORWARD_DECLARE_2(engine, scene, Scene2D);
PROPELLER_FORWARD_DECLARE_2(engine, input, Input);

#define DEFINE_COMPONENT(p_name)\
	DEFINE_CLASS(p_name);\
	GENERATE_STATIC_PROPERTY_VECTOR;\
	GENERATE_COMPONENT_DEPENDENCY_LIST;

namespace engine {
namespace component {

	class ComponentHolder;

	class Component : public engine::stream::Serializable
	{
	private:
		ComponentHolder *parent;

		DEFINE_CLASS(Component);

		GENERATE_VIRTUAL_COMPONENT_DEPENDENCY_LIST;

		virtual engine::properties::PropertyVector& getProperties() const 
		{
			LOG_ERROR("Properties are not enabled for this component");
			//DEBUG_BREAK;
			static engine::properties::PropertyVector staticPropertyVector;
			return staticPropertyVector;
		}

	public:
		Component(void *context);

		virtual ~Component(){}; 

		virtual void init() { };
		virtual void uninit() { };

		ComponentHolder *getParent();

		void setParent(ComponentHolder *parent);

		void save(stream::OutputStream<stream::SerializationEndian> &strm) const {}
		void load(stream::InputStream<stream::SerializationEndian> &strm) {}
	};

} /* component */
} /* engine */

#endif /* Component_H */
