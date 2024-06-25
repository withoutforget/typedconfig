#pragma once

#include <vector>
#include <algorithm>
#include <memory>
#include <utility>
#include "var.hpp"

#include <iostream>

namespace typedconfig {
	class var_manager {
	private:
		std::vector<var*> m_types;
		var_manager() = default;
	public:
		static var_manager& instance() {
			static var_manager vm;
			return vm;
		}

		template<typename T, typename ... Ts>
		void import(Ts&& ... ts) {
			m_types.emplace_back(new T{ std::forward<Ts>(ts)... });
		}

		std::unique_ptr<var> create(std::string_view type) const {
			auto it = std::find_if(m_types.begin(), m_types.end(), [type](var* p) { return p->get_type() == type; });
			if (it == m_types.end())
				return {};
			return std::unique_ptr<var>{ (*it)->clone() };
		}

		std::unique_ptr<var> construct(std::string_view type, std::string_view name, std::string_view value) const {
			auto p = create(type);
			if (!p)
				throw std::runtime_error{std::format("Cannot find type '{}'", type)};
			p->set_name(name);
			p->set_value(value);
			return p;
		}
	};
}