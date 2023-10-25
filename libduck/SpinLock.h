/*
	hfd
*/

#pragma once

#include <sys/types.h>
#include <atomic>

#define LOCK(l) Duck::ScopedLock __lock(l);

namespace Duck {
	class SpinLock {
	public:
		SpinLock() = default;
		void acquire();
		void release();

	private:
		std::atomic<int> times_locked = {0};
	};

	class ScopedLock {
	public:
		explicit ScopedLock(SpinLock& lock);
		~ScopedLock();
	private:
		SpinLock& lock;
	};
}

