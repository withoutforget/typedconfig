#pragma once
#include <string>
#include <string_view>
#include <format>

namespace typedconfig {
	 
	class formatter {
	public:
		virtual ~formatter() = default;

		virtual std::string serialize(std::string_view type, std::string_view name, std::string_view value) const {
			return std::format("{}:{}={}", type, name, value);
		}
		virtual std::tuple<std::string, std::string, std::string> deserialize(std::string_view inp) const {
			auto string_begin = inp.find_first_not_of(' ') - 1;
			auto colon_pos = inp.find(':');
			auto eq_pos = inp.find('=');

			if (string_begin == std::string_view::npos)
				string_begin = 0;

			if (colon_pos == std::string_view::npos || eq_pos == std::string_view::npos || colon_pos > eq_pos)
				throw std::runtime_error{std::format("Error while parsing '{}': Wrong format.", inp)};

			auto type = inp.substr(string_begin, colon_pos - string_begin);
			auto name = inp.substr(colon_pos + 1, eq_pos - colon_pos - 1);
			auto value = inp.substr(eq_pos + 1);

			if (type.empty() || name.empty())
				throw std::runtime_error{std::format("Error while parsing '{}'. type or name must not be empty", inp)};

			return { std::string{type}, std::string{name}, std::string{value} };
		}
	};
}