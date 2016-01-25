// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_DEBUG_DEBUG_H
#define ENGINE_DEBUG_DEBUG_H

#ifndef _RELEASE
	#ifdef _WIN32 
        #define DEBUG_BREAK __debugbreak();
		#define DEBUG_PRINT(p_msg)do{\
			std::stringstream __stringStream__;\
			__stringStream__ << p_msg;\
			engine::debug::debugPrint(__stringStream__.str());}\
			while(false);
	#endif

	#ifdef _LINUX
		//#define DEBUG_PRINT(p_msg) printf("%s", p_msg);
		#define DEBUG_PRINT(p_msg)
		#define DEBUG_BREAK
	#endif

	#ifdef _ANDROID
		// Debug printing on android disabled right now TODO
		#define DEBUG_PRINT(p_msg)
		#define DEBUG_BREAK {} ;
	#endif
#else
	#define DEBUG_PRINT(p_msg)
	#define DEBUG_BREAK {};
#endif

#ifdef OS_WEB
	#define DEBUG_PRINT()
	#define DEBUG_BREAK {};
#endif

namespace engine {
namespace debug {

	void debugPrint(const std::string &p_msg);
	void debugBreakpoint();

}
}


#endif
