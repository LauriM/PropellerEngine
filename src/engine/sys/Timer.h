// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYS_TIMER_H
#define ENGINE_SYS_TIMER_H

namespace engine {
namespace sys {

	// Init the timer system
	void initTimer();

	class Timer
	{
	private:
#ifdef OS_WINDOWS
		LARGE_INTEGER startTime;
		LARGE_INTEGER endTime;
#endif

#if defined(OS_LINUX) || defined(OS_ANDROID)
		timespec startTime;
		timespec endTime;
#endif

		bool stopped;
	public:
		Timer();

		// Start the timer, reset from start if not stopped
		void start();
		void stop();

		long getTimeInMicroSeconds();
		long getTimeInMilliSeconds();
		long getTimeInSeconds();

		static double getCurrentTimeInSeconds();
	};

}
}

#endif
