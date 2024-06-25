#pragma once 

#include "var.hpp"
#include <concepts>

namespace typedconfig {

	template<typename T>
	class number_var {};

	template<std::integral T>
	class number_var<T> : virtual public var {
	protected:
		std::string m_name{};
		T m_value{};
		int m_base = 10;
	public:
		number_var() {}
		number_var(std::string_view name, T value = T{}) : m_name(name), m_value(value) {}

		std::string_view get_name() const final { return m_name; }
		std::string get_value() const final { return utils::number_to_str(m_value, m_base); }
		virtual int get_base() const { return m_base; }

		void set_name(std::string_view name) final { m_name = name; }
		void set_value(std::string_view value) final { m_value = utils::str_to_number<T>(value, m_base);; }
		virtual void set_base(int base) { m_base = base; }
	};

	template<std::floating_point T>
	class number_var<T> : virtual public var {
	protected:
		std::string m_name{};
		T m_value{};
		int m_precision = -1;
	public:
		number_var() {}
		number_var(std::string_view name, T value = T{}) : m_name(name), m_value(value) {}

		std::string_view get_name() const final { return m_name; }
		std::string get_value() const final {
			if (m_precision == -1)
				return utils::number_to_str(m_value);
			else
				return utils::number_to_str(m_value, m_precision);
		}
		virtual int get_precision() const { return m_precision; }

		void set_name(std::string_view name) final { m_name = name; }
		void set_value(std::string_view value) final { m_value = utils::str_to_number<T>(value); }
		virtual void set_precision(int precision) { m_precision = precision; }
	};

	class i32 : virtual public number_var<__int32> {
	public:
		using value_type = __int32;
	public:
		i32() {}
		i32(std::string_view name, int value = 0) : number_var<__int32>(name, value) {}

		std::string_view get_type() const final { return "i32"; }

		std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new i32()); }
	};
	class f64 : virtual public number_var<double> {
	public:
		using value_type = double;
	public:
		f64() {}
		f64(std::string_view name, double value = 0) : number_var<double>(name, value) {}

		std::string_view get_type() const final { return "f64"; }

		std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new f64()); }
	};
}