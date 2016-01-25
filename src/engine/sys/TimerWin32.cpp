// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#ifdef OS_WINDOWS

#include "engine/sys/Timer.h"

namespace engine {
namespace sys {

	LARGE_INTEGER g_timerFrequency;

	void initTimer()
	{
		QueryPerformanceFrequency(&g_timerFrequency);
	}

	/*
	long long getCurrentTime()
	{
		LARGE_INTEGER largeInt;

		QueryPerformanceCounter(&largeInt);

		return largeInt.QuadPart;
	}
	*/

	Timer::Timer()
		: stopped(false)
	{ }

	void Timer::start()
	{
		QueryPerformanceCounter(&startTime);
		stopped = false;
	}

	void Timer::stop()
	{
		QueryPerformanceCounter(&endTime);
		stopped = true;
	}

	long Timer::getTimeInMicroSeconds()
	{
		if (!stopped) // timer is still running, update the endTime, keep timer running
			QueryPerformanceCounter(&endTime);

		LARGE_INTEGER elapsed;
		elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;

		elapsed.QuadPart *= 1000000; // converting to microseconds
		elapsed.QuadPart /= g_timerFrequency.QuadPart;

		return long(elapsed.QuadPart);
	}

	long Timer::getTimeInMilliSeconds()
	{
		if (!stopped) // timer is still running, update the endTime, keep timer running
			QueryPerformanceCounter(&endTime);

		LARGE_INTEGER elapsed;
		elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;

		elapsed.QuadPart *= 1000000; // converting to microseconds
		elapsed.QuadPart /= g_timerFrequency.QuadPart;

		return long(elapsed.QuadPart) / 1000;
	}

	long Timer::getTimeInSeconds()
	{
		if (!stopped) // timer is still running, update the endTime, keep timer running
			QueryPerformanceCounter(&endTime);

		LARGE_INTEGER elapsed;
		elapsed.QuadPart = endTime.QuadPart - startTime.QuadPart;

		elapsed.QuadPart *= 1000000; // converting to microseconds
		elapsed.QuadPart /= g_timerFrequency.QuadPart;

		return long(elapsed.QuadPart) / 1000000;
	}

	// Static timer function
	double Timer::getCurrentTimeInSeconds()
	{
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);

		time.QuadPart *= 1000000; // converting to microseconds
		time.QuadPart /= g_timerFrequency.QuadPart;;

		return double(time.QuadPart) / 1000000;
	}

}
}

#endif
