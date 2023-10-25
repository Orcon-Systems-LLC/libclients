

#pragma once

#include <string>
#include <stdexcept>

namespace UI {
	class UIException: public std::runtime_error {
	public:
		UIException(const std::string& description);
	};
}


