// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"
#include "engine/SystemBase.h"

#include "engine/component/Component.h"
#include "engine/profiler/AutoProfiler.h"

#ifdef _EDITOR
#include <time.h>
#endif

namespace engine {

	void SystemBase::addComponent(component::Component *component)
	{
		PROFILE;
		components.push_back(component);
	}

	void SystemBase::removeComponent(component::Component *component)
	{
		PROFILE;
		for (unsigned i = 0; i < components.size(); ++i)
		{
			if (components[i] == component)
			{
				components.erase(components.begin() + i);
				return;
			}
		}
	}

}