// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_AUDIO_AUDIODEVICEBASE_H
#define ENGINE_AUDIO_AUDIODEVICEBASE_H

namespace engine {
namespace audio {

	class AudioDeviceBase
	{
		// Init and uninit the audio device
		void init();
		void uninit();

		// void PlayAudioAtLocation(Vec3 pos, AudioResource *res);
		// etc...
	};

}
}

#endif