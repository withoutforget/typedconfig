#pragma once

#include <memory>
#include <vector>
#include <type_traits>

#include "formatter.h"
#include "var.hpp"

namespace typedconfig {
	class config {
	private:
		std::vector<std::unique_ptr<var>> m_data;
		std::unique_ptr<formatter> m_formatter{ new formatter{} };
	public:
		config() = default;

		template<typename T, typename ... Ts>
		void append(Ts&& ... args) {
			m_data.emplace_back(new T(std::forward<Ts>(args)...));
		}

		void append(std::unique_ptr<var>&& object) {
			m_data.emplace_back(std::move(object));
		}

		template<typename Formatter>
			requires std::is_base_of_v<formatter, Formatter>
		void set_formatter(const Formatter& formatter) {
			m_formatter.reset(new Formatter(formatter));
		}

		formatter* get_formatter() const {
			return m_formatter.get();
		}

		std::string dump(char delimiter = '\n') const {
			std::string str{};
			for (auto&& p : m_data)
				str += p->dump(*m_formatter) + delimiter;
			return str;
		}

		void parse(std::string_view data, char delimiter = '\n') {
			size_t last_position = 0;
			while (true) {
				auto next_pos = data.find(delimiter, last_position + 1);
				if (next_pos == std::string_view::npos) {
					auto&& [type, name, value] = m_formatter->deserialize(data.substr(last_position, data.size() - last_position));
					append(var_manager::instance().construct(type, name, value));
					break;
				}
				auto&& [type, name, value] = m_formatter->deserialize(data.substr(last_position, next_pos - last_position - 1));
				append(var_manager::instance().construct(type, name, value));
				last_position = next_pos + 1;
			}
		
		}

	};
}