// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#include "engine/precompiled.h"

#include "engine/sys/Scheduler.h"
#include "engine/sys/Sleep.h"
#include "engine/stream/InputStream.h"
#include "engine/sys/Atomic.h"

namespace engine {
namespace sys {

	void Scheduler::staticWorkerEntry(void *s)
	{
		PROFILE;

		LOG_INFO("[Scheduler] Worker starting with thread ID: " << propellerGetCurrentThreadID());
		Scheduler *scheduler = (Scheduler*)s;

		WorkerState state = WORKER_CONTINUE;
		while (state == WORKER_CONTINUE)
		{
			state = scheduler->workerEntrypoint();
		}
	}

	Scheduler::Scheduler()
		: shutdownInProcess(false)
	{
		queueMutex = createMutex();
	}

	void Scheduler::init(unsigned workerCount)
	{
		this->workerCount = workerCount;

		for (unsigned i = 0; i < workerCount; ++i)
		{
			std::stringstream ss;
			ss << "Worker_";
			ss << i;
			Thread *worker = propellerCreateThread(ss.str(), &staticWorkerEntry, this);

			workers.push(worker);
		}
	}

	Scheduler::~Scheduler()
	{
		shutdownInProcess = true;

		while (workerCount > 0)
		{
			// Wait for the workes to die
			propellerSleep(50);
		}
	}

	WorkerState Scheduler::workerEntrypoint()
	{
		PROFILE;
		// Something in queue, go in with mutex
		waitAndTakeMutex(queueMutex);

		if (shutdownInProcess == true)
		{
			--workerCount;
			propellerSleep(5);
			return WORKER_DIE;
		}

		unsigned jobCount = 10;
		JobDecl *jobs[10];

		if (queue.getSize() > 0)
		{
			if (queue.getSize() < jobCount)
				jobCount = queue.getSize();

			// Take jobs! Jobcount, or max size of queue
			for (unsigned i = 0; i < jobCount; ++i)
				jobs[i] = queue.pop();

			// Ok, jobs taken, lets release mutex
			releaseMutex(queueMutex);

			// HANDLE THE JOBS
			for (unsigned i = 0; i < jobCount; ++i)
			{
				jobs[i]->func(jobs[i]->userdata);
				AtomicDecrement(jobs[i]->counter);
			}
			// JOB DONE

			return WORKER_CONTINUE;
		}

		// Jobs were taken before us, release mutex and continue
		releaseMutex(queueMutex);

		return WORKER_CONTINUE;
	}

	void Scheduler::runJobs(JobDecl *jobs, unsigned jobCount)
	{
		waitAndTakeMutex(queueMutex);

		for (unsigned i = 0; i < jobCount; ++i)
			queue.push(&jobs[i]);

		releaseMutex(queueMutex);
	}

}
}
