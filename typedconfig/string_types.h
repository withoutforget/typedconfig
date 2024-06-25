#pragma once

#include "var.hpp"

#include "formatter.h"

namespace typedconfig {
	class string_var : public virtual var {
	private:
		std::string m_name;
		std::string m_value;
	public:
		string_var() = default;
		string_var(std::string_view name, std::string_view value = "") : m_name(name), m_value(value) {}
		virtual ~string_var() = default;

		std::string_view get_type() const final { return "str"; }
		std::string_view get_name() const final { return m_name; }
		std::string get_value() const final { return m_value; }
		
		void set_name(std::string_view name) final { m_name = name; }
		void set_value(std::string_view value) final { m_value = value; }
		
		std::unique_ptr<var> clone() const final {
			return std::unique_ptr<var>(new string_var());
		}
	};

	namespace types {
		using str = string_var;
	}
}