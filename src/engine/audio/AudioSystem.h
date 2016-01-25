// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_AUDIO_AUDIOSYSTEM_H
#define ENGINE_AUDIO_AUDIOSYSTEM_H

#include "engine/SystemBase.h"

namespace engine {
namespace audio {

	class AudioSystem : public engine::SystemBase
	{
	private:
	public:
		const String getName() { return "AudioSystem"; }

		bool init();
		void uninit();
		void update(float delta);
	};

}
}

#endif