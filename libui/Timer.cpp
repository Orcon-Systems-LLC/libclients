/*
	hfd
*/

#include "Timer.h"
#include "libui.h"

using namespace UI;

Timer::Timer() = default;

Timer::Timer(int id, int delay, std::function<void()> call, bool is_interval):
	m_id(id), m_delay(delay), m_call(std::move(call)), m_interval(is_interval)
{
	calculate_trigger_time();
}

Timer::~Timer() {
	UI::remove_timer(m_id);
}

void Timer::calculate_trigger_time() {
	m_trigger_time = Duck::Time::now() + Duck::Time::millis(m_delay);
}

[[nodiscard]] bool Timer::ready() const {
	return millis_until_ready() <= 0;
}

[[nodiscard]] long Timer::millis_until_ready() const {
	return (m_trigger_time - Duck::Time::now()).millis();
}

void Timer::stop() {
	m_enabled = false;
}

void Timer::start() {
	m_enabled = true;
	calculate_trigger_time();
}
