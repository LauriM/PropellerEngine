// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_COMPONENT_DEPENDENCIES_H
#define ENGINE_COMPONENT_DEPENDENCIES_H

#include "engine/rtti/Class.h"
#include "engine/rtti/RTTI.h"

// Editor builds of the engine will have Component dependency system enables. This prevents the user from crashing the game by removing/adding components in the wrong order.

namespace engine {
namespace component {

	typedef std::vector<String> DependencyList;

}
}

#ifdef _EDITOR

#define GENERATE_COMPONENT_DEPENDENCY_LIST \
	engine::component::DependencyList& getDependencyList() const \
	{\
		static engine::component::DependencyList staticDependencyList;\
		return staticDependencyList;\
	}

#define GENERATE_VIRTUAL_COMPONENT_DEPENDENCY_LIST\
	virtual GENERATE_COMPONENT_DEPENDENCY_LIST;

#define BEGIN_DEPENDENCIES(p_class)\
	class DependenciesHelper##p_class;\
	typedef DependenciesHelper##p_class DependencyClass;\
	class DependenciesHelper##p_class { \
	public:\
		DependenciesHelper##p_class(){\
			p_class c(NULL);

// Do not add namespaces for the component!
#define REQUIRE_COMPONENT(p_component)\
	c.getDependencyList().push_back(TO_STRING(p_component));

#define END_DEPENDENCIES\
		}\
	};\
	DependencyClass dependencyHelperClass;\

#else
//The editor is not in use, disable all the dependency checking.

#define GENERATE_COMPONENT_DEPENDENCY_LIST
#define REQUIRE_COMPONENT(p_component)
#define GENERATE_VIRTUAL_COMPONENT_DEPENDENCY_LIST
#define BEGIN_DEPENDENCIES(p_class)
#define REQUIRE_COMPONENT(p_component)
#define END_DEPENDENCIES

#endif

#endif