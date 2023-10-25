/*
	hfd
*/

#include "Time.h"

using namespace Duck;

Time::Time(): m_sec(0), m_usec(0) {}
Time::Time(int64_t sec, long usec): m_sec(sec), m_usec(usec) {}
Time::Time(timeval val): m_sec(val.tv_sec), m_usec(val.tv_usec) {}

Time Time::now() {
	timeval tv;
	gettimeofday(&tv, nullptr);
	return Time {tv};
}


Time Time::operator+(const Time& other) const {
	Time ret(*this);
	ret.m_usec += other.m_usec;
	ret.m_sec += other.m_sec + ret.m_usec / 1000000;
	ret.m_usec %= 1000000;
	return ret;
}


Time Time::operator- (const Time& other) const {
	Time ret(*this);
	ret.m_sec -= other.m_sec;
	ret.m_usec -= other.m_usec;
	if(ret.m_usec < 0) {
		ret.m_sec -= 1 + ret.m_usec / -1000000;
		ret.m_usec = (1000000 - (-ret.m_usec % 1000000)) % 1000000;
	}
	return ret;
}

bool Time::operator>(const Time& other) const {
	return m_sec > other.m_sec || (m_sec == other.m_sec && m_usec > other.m_usec);
}

bool Time::operator>=(const Time& other) const {
	return m_sec > other.m_sec || (m_sec == other.m_sec && m_usec >= other.m_usec);
}

bool Time::operator<(const Time& other) const {
	return m_sec < other.m_sec || (m_sec == other.m_sec && m_usec < other.m_usec);
}

bool Time::operator<=(const Time& other) const {
	return m_sec < other.m_sec || (m_sec == other.m_sec && m_usec <= other.m_usec);
}

bool Time::operator==(const Time& other) const {
	return m_sec == other.m_sec && m_usec == other.m_usec;
}