// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#define BOOST_SIGNALS_NO_DEPRECATION_WARNING

//TODO: Move platform related stuff away from the precompiled!

#include "engine/preprocessor/platform.h"

#if defined (_MAC)
#include <malloc/malloc.h>
#else
	#include <malloc.h>
#endif

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <boost/unordered_map.hpp>
#include <boost/move/move.hpp>
#include <json/json.h>

#ifdef _WIN32
#define _WINSOCKAPI_
#include <windows.h>
#endif

#ifdef D3D11
#include <d3d11.h>
#include <d3dcompiler.h>
#endif

#include "engine/preprocessor/version.h"
#include "engine/preprocessor/forwardDeclare.h"
#include "engine/math/Constants.h"
#include "engine/lang/RCCPP.h"

//Strings are funny
typedef std::string String;

#define _TO_STRING(value) #value
#define TO_STRING(value) _TO_STRING(value)

#include "engine/debug/Debug.h"
#include "engine/debug/Tombstone.h"
#include "engine/sys/Logger.h"
#include "engine/profiler/AutoProfiler.h"

#ifdef OS_WEB
#define DEBUG_PRINT(p_name) {}
#endif