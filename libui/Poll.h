/*
	hfd
*/

#pragma once

#include <functional>

namespace UI {
	class Poll {
	public:
		int fd;
		std::function<void()> on_ready_to_read = nullptr;
		std::function<void()> on_ready_to_write = nullptr;
	};
}

