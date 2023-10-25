/*
	hfd
*/

#pragma once

#include <string>
#include <utility>
#include "Stream.h"

namespace Duck {
	class StringInputStream: public InputStream {
	public:
		explicit StringInputStream(std::string string): m_string(std::move(string)) {}

		//InputStream
		size_t read(void* buffer, size_t n) override;
		Result seek(long offset, Whence whence) override;
		[[nodiscard]] bool eof() const override { return m_eof; }

	private:
		std::string m_string;
		size_t m_offset = 0;
		bool m_eof = false;
	};

	class StringOutputStream: public OutputStream {
	public:
		const std::string& string() { return m_string; }

		//OutputStream
		size_t write(const void* buffer, size_t n) override;
		Result seek(long seek, Whence whence) override;

	private:
		std::string m_string;
		size_t m_offset = 0;
	};

}


