// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_AUDIO_AUDIODEVICE_H
#define ENGINE_AUDIO_AUDIODEVICE_H

#include "engine/audio/AudioType.h"

#ifdef XAUDIO2
#include "engine/audio/XAudio2/XAudio2Device.h"
#endif

#ifndef AUDIO_ENABLED
typedef int AudioDevice;
#endif

#endif