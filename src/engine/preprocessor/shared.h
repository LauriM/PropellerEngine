// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
//_EDITOR == Runtime compiled

#if _EDITOR 
	#define SHAREDENGINE __declspec(dllexport)

	#ifdef GAME
		#define SHAREDGAME __declspec(dllexport)
	#endif

	#ifdef EDITORBACKEND
		#define SHAREDGAME __declspec(dllimport)
	#endif
#else
	#define SHAREDGAME 
	#define SHAREDENGINE 
#endif