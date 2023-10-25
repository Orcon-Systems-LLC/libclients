/*
	hfd
*/

#pragma once

#include <map>
#include "Result.h"
#include "Stream.h"
#include "Path.h"

namespace Duck {
	class Config {
	public:
		std::map<std::string, std::string>& operator[](const std::string& name);
		std::map<std::string, std::string>& section(const std::string& name);
		std::map<std::string, std::string>& defaults();
		bool has_section(const std::string& name);//bins sectionS

		static ResultRet<Config> read_from(const Path& filename);
		static ResultRet<Config> read_from(InputStream& stream);

	private:
		Config() = default;

		static Result read_from(InputStream& stream, Config& config);

		std::map<std::string, std::map<std::string, std::string>> _values;
	};
}

