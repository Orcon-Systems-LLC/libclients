/*
	hfd
*/

#include "SpinLock.h"
#include <sys/thread.h>

void Duck::SpinLock::acquire() {
	while(times_locked.exchange(1, std::memory_order_acquire));
}

void Duck::SpinLock::release() {
	times_locked.store(0, std::memory_order_release);
}

Duck::ScopedLock::ScopedLock(Duck::SpinLock& lock): lock(lock) {
	lock.acquire();
}

Duck::ScopedLock::~ScopedLock() {
	lock.release();
}
