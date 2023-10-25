/*
	hfd
*/

#pragma once

#include <string>
#include <vector>
#include "Result.h"

namespace Duck {
	class DirectoryEntry;
	class Path {
	public:
		Path(): Path("/") {}
		Path(const char* c_string): Path(std::string(c_string)) {}
		Path(std::string string);

		//Path
		[[nodiscard]] bool is_absolute() const { return m_is_absolute; }
		[[nodiscard]] const std::string& basename() const { return m_parts.back(); }
		[[nodiscard]] const std::string& filename() const { return m_filename; }
		[[nodiscard]] const std::string& string() const { return m_path; }
		[[nodiscard]] const std::string& extension() const { return m_extension; }
		[[nodiscard]] Path parent() const { return operator/(".."); }

		//Conversion and operators
		operator std::string() const;
		Path operator/(const Path& other) const { return Path(string() + "/" + other.string()); }
		Path operator/(const std::string& other) const { return operator/(Path(other)); }
		Path operator/(const char* other) const { return operator/(Path(other)); }
		bool operator==(const Path& other) const { return m_path == other.m_path; }

		//Directory iteration
		[[nodiscard]] ResultRet<std::vector<DirectoryEntry>> get_directory_entries() const;

	private:
		void rebuild_parts();

		std::vector<std::string> m_parts;
		std::string m_extension = "";
		std::string m_filename = "";
		std::string m_path = "";
		bool m_is_absolute = false;
	};
}

#include "DirectoryEntry.h"