/*
	hfd
*/

#pragma once

#include <string>
#include <algorithm>

namespace Duck {
	inline std::string& rtrim(std::string& str) {
		str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) {
			return !std::isspace(c);
		}).base(), str.end());
		return str;
	}

	inline std::string& ltrim(std::string& str) {
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {
			return !std::isspace(c);
		}));
		return str;
	}

	inline std::string& trim(std::string& str) {
		return ltrim(rtrim(str));
	}
}

