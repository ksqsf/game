#pragma once

#include <string>
#include <stdexcept>

struct SDLException : std::runtime_error {
	explicit SDLException(const std::string& s) : std::runtime_error(s) { }
};
