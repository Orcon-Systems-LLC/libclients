/*
	hfd
*/

#pragma once

#include "sys/time.h"

namespace Duck {
	class Time {
	public:
		Time();
		Time(int64_t sec, long usec);
		explicit Time(timeval val);

		[[nodiscard]] static Time now();
		[[nodiscard]] static Time millis(long millis) { return {millis / 1000, (millis % 1000) * 1000}; }

		[[nodiscard]] timeval to_timeval() const { return {m_sec, m_usec}; }
		[[nodiscard]] int64_t epoch() const { return m_sec; }
		[[nodiscard]] long interval_usec() const { return m_usec; }
		[[nodiscard]] long millis() const { return ((long) m_sec * 1000) + (m_usec / 1000); }

		Time operator+(const Time& other) const;
		Time operator-(const Time& other) const;
		bool operator>(const Time& other) const;
		bool operator>=(const Time& other) const;
		bool operator<(const Time& other) const;
		bool operator<=(const Time& other) const;
		bool operator==(const Time& other) const;

	private:
		int64_t m_sec;
		long m_usec;
	};
}