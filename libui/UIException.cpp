

#include "UIException.h"

UI::UIException::UIException(const std::string& description): std::runtime_error(description) {
}
