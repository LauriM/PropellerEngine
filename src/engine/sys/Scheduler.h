// Copyright (c) Lauri Mäkinen 2014 - 2015
// All rights reserved.
#ifndef ENGINE_SYS_SCHEDULER_H
#define ENGINE_SYS_SCHEDULER_H

#include "engine/util/Array.h"
#include "engine/sys/Thread.h"
#include "engine/util/Bind.h"
#include "engine/sys/Mutex.h"

#define PROPELLER_JOB_ENTRYPOINT(p_class, p_task, p_vartype, p_varname)

namespace engine {
namespace sys {

	enum WorkerState
	{
		WORKER_CONTINUE = 0,
		WORKER_DIE,
	};

	struct JobDecl
	{
		void (*func)(void *);
		void *userdata;
		volatile unsigned *counter;
	};

	class Scheduler
	{
	private:
		util::Array<Thread*> workers;
		unsigned workerCount;

		bool shutdownInProcess;

		util::Array<JobDecl*> queue;

		sys::Mutex *queueMutex;
	public:
		Scheduler();
		~Scheduler();

		void init(unsigned workerCount);

		WorkerState workerEntrypoint();

		JobDecl declareJob(void (*func)(void*), volatile unsigned *counter, void *userdata)
		{
			JobDecl decl;
			decl.counter = counter;
			decl.func = func;
			decl.userdata = userdata;

			return decl;
		}

		void runJobs(JobDecl *jobs, unsigned jobCount);

		static void staticWorkerEntry(void *scheduler);
	};

}
}

#endif