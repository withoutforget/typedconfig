#pragma once
#include <string_view>
#include <charconv>
#include <concepts>

namespace typedconfig {
	namespace utils {
		template<std::integral T>
		T str_to_number(std::string_view s, int base = 10) {
			T val{};
			std::from_chars(s.data(), s.data() + s.size(), val, base);
			/* TODO: handle errors here */
			return val;
		}
		template<std::floating_point T>
		T str_to_number(std::string_view s) {
			T val{};
			std::from_chars(s.data(), s.data() + s.size(), val);
			return val;
		}

		template<std::integral T>
		std::string number_to_str(T number, int base = 10) {
			std::string val;
			val.resize(sizeof(std::string));
			std::to_chars(val.data(), val.data() + val.size(), number, base);
			return val;
		}

		template<std::floating_point T>
		std::string number_to_str(T number, int precision = -1) {
			std::string val;
			val.resize(sizeof(std::string));
			if (precision == -1)
				std::to_chars(val.data(), val.data() + val.size(), number);
			else
				std::to_chars(val.data(), val.data() + val.size(), number, std::chars_format::general, precision);
			return val;
		}
	}
}