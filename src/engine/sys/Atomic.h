// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYS_ATOMIC_H
#define ENGINE_SYS_ATOMIC_H

namespace engine {
namespace sys {

	void AtomicIncrement(volatile unsigned *value);
	void AtomicDecrement(volatile unsigned *value);

}
}

#endif