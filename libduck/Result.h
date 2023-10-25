/*
	hfd
*/

#pragma once

#include <cassert>
#include <optional>
#include <cstring>
#include <string>

#define TRY(expr) \
	({ \
        auto res = (expr); \
        if (res.is_error()) \
            return res.result(); \
        res.value(); \
    })

namespace Duck {
	class Result {
	public:
		Result(int code): m_code(code) {}
		Result(int code, std::string message): m_code(code), m_message(std::move(message)) {}
		Result(std::string message): m_code(FAILURE.m_code), m_message(std::move(message)) {}

		[[nodiscard]] bool is_success() const { return m_code == 0; }
		[[nodiscard]] bool is_error() const { return m_code; }
		[[nodiscard]] int code() const { return m_code; }
		[[nodiscard]] const char* strerror() const { return has_message() ? m_message.c_str() : ::strerror(m_code); }
		[[nodiscard]] bool has_message() const { return !m_message.empty(); }
		[[nodiscard]] std::string message() const { return has_message() ? m_message.c_str() : ::strerror(m_code); }
		operator int() const { return m_code; }

		static const Result SUCCESS;
		static const Result FAILURE;

	private:
		int m_code;
		std::string m_message;

	};

	template<typename T>
	class ResultRet {
	public:
		ResultRet(Result error): m_ret(std::nullopt), m_result(error) {};
		ResultRet(std::optional<T> ret): m_ret(std::move(ret)), m_result(0) {};
		ResultRet(T ret): m_ret(std::move(ret)), m_result(0) {};

		[[nodiscard]] bool is_error() const { return m_result.is_error(); }
		[[nodiscard]] bool has_value() const { return m_ret.has_value(); }
		[[nodiscard]] int code() const { return m_result.code(); }
		[[nodiscard]] Result result() const { return m_result; }
		[[nodiscard]] const char* strerror() const { return m_result.strerror(); }
		[[nodiscard]] std::string message() const { return m_result.message(); }
		[[nodiscard]] bool has_message() const { return m_result.has_message(); }
		[[nodiscard]] T& value() { return m_ret.value(); };
		[[nodiscard]] constexpr T value_or(T&& alt) && { return m_ret.value_or(std::forward<T>(alt)); }
		operator T&() { return m_ret.value(); }

	private:
		std::optional<T> m_ret;
		Result m_result;
	};
}