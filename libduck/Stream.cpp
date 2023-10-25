/*
	hfd
*/

#include "Stream.h"
#include "FileStream.h"

using namespace Duck;

[[maybe_unused]] InputStream& Stream::std_in = FileStream::std_in;
[[maybe_unused]] OutputStream& Stream::std_out = FileStream::std_out;
[[maybe_unused]] OutputStream& Stream::std_err = FileStream::std_err;

Stream::~Stream() = default;

[[nodiscard]] Result Stream::status(){
	auto ret = m_err;
	m_err = 0;
	return ret;
}


/*
 * Stream operators
 */
namespace Duck {
	/*
	 * InputStream stuff
	 */

	InputStream& operator>>(InputStream& stream, uint8_t& byte) {
		stream.read(&byte, 1);
		return stream;
	}

	InputStream& operator>>(InputStream& stream, char& chr) {
		stream.read(&chr, 1);
		return stream;
	}

	InputStream& operator>>(InputStream& stream, std::string& string) {
		string = "";
		char read;
		size_t nread = stream.read(&read, 1);

		while(read != stream.delimeter() && nread) {
			string += read;
			nread = stream.read(&read, 1);
		}

		return stream;
	}

	/*
	 * OutputStream strings
	 */

	OutputStream& operator<<(OutputStream& stream, const char* chars) {
		stream.write(chars, strlen(chars));
		return stream;
	}

	OutputStream& operator<<(OutputStream& stream, const std::string& string) {
		stream.write(string.c_str(), string.size());
		return stream;
	}

	OutputStream& operator<<(OutputStream& stream, const std::string_view& view) {
		stream.write(view.data(), view.size());
		return stream;
	}

	/*
	 * OutputStream primitives
	 */

	OutputStream& operator<<(OutputStream& stream, char chr) {
		stream.write(&chr, 1);
		return stream;
	}

	OutputStream& operator<<(OutputStream& stream, const uint8_t& byte) {
		stream.write(&byte, 1);
		return stream;
	}

	OutputStream& operator<<(OutputStream& stream, int value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, long value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, float value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, double value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, long long value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, long double value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, unsigned int value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, unsigned long value) {
		return operator<<(stream, std::to_string(value));
	}

	OutputStream& operator<<(OutputStream& stream, unsigned long long value) {
		return operator<<(stream, std::to_string(value));
	}
}