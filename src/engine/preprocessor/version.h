// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef VERSION_H
#define VERSION_H

#define ENGINE_VERSION_MAJOR 1
#define ENGINE_VERSION_MINOR 0
#define ENGINE_VERSION_PATCH 7

#ifdef _DEBUG
	#define ENGINE_VERSION_TYPE "Dev"
#else
	#define ENGINE_VERSION_TYPE "Release"
#endif

#endif