// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#if defined(OS_LINUX) || defined(OS_ANDROID)

#include <sys/time.h>
#include <time.h>

namespace engine {
namespace sys {

	void initTimer() { }

	Timer::Timer()
		: stopped(true)
	{ }

	void Timer::start()
	{
		clock_gettime(CLOCK_MONOTONIC, &startTime);
		stopped = false;
	}

	void Timer::stop()
	{
		clock_gettime(CLOCK_MONOTONIC, &endTime);
		stopped = true;
	}

	long Timer::getTimeInMicroSeconds()
	{
		if (!stopped)
			clock_gettime(CLOCK_MONOTONIC, &endTime);

		return (endTime.tv_nsec - startTime.tv_nsec) / 1000;
	}

	long Timer::getTimeInMilliSeconds()
	{
		if (!stopped)
			clock_gettime(CLOCK_MONOTONIC, &endTime);

		return (endTime.tv_nsec - startTime.tv_nsec) / 1000000;
	}

	long Timer::getTimeInSeconds()
	{
		if (!stopped)
			clock_gettime(CLOCK_MONOTONIC, &endTime);

		return (endTime.tv_nsec - startTime.tv_nsec) / 1000000000;
	}

	double Timer::getCurrentTimeInSeconds()
	{
		timespec time;
		clock_gettime(CLOCK_MONOTONIC, &time);

		return time.tv_nsec / 1000000000.f;
	}

}
}

#endif
