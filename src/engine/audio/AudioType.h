// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_AUDIO_AUDIOTYPE_H
#define ENGINE_AUDIO_AUDIOTYPE_H

#include "engine/preprocessor/platform.h"

#ifdef OS_ANDROID
#ifndef OPENSL 
#define OPENSL
#endif
#endif

#ifdef OS_WINDOWS
#ifndef XAUDIO2
#define XAUDIO2
#endif
#endif

#ifdef XAUDIO2 
#define AUDIO_ENABLED 1
#endif

#ifdef OPENSL
#define AUDIO_ENABLED 1
#endif

#endif