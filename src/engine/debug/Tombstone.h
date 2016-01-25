// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_DEBUG_TOMBSTONE_H
#define ENGINE_DEBUG_TOMBSTONE_H

// Used to detect dead code effectively

#ifdef _RELEASE
	#define TOMBSTONE(p_time)
#else
#define TOMBSTONE(p_time) LOG_INFO(">>TOMBSTONE<< " << __FILE__ << ":" << __LINE__ << ":" << TO_STRING(p_time));\
	assert(false);
#endif

#endif