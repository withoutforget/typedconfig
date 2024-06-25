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
		virtual ~number_var() = default;

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
		virtual ~number_var() = default;

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
	namespace types {

		class boolean : virtual public var {
		private:
			std::string m_name;
			bool m_value{};
		public:
			boolean() = default;
			boolean(std::string_view name, bool value = {}) : m_name(name), m_value(value) {}

			std::string_view get_type() const final { return "boolean"; }
			std::string_view get_name() const final { return m_name; }
			std::string get_value() const final { return utils::number_to_str<int>(m_value); }

			void set_name(std::string_view name) final { m_name = name; }
			void set_value(std::string_view value) final {
				m_value = utils::str_to_number<int>(value);
			}

			std::unique_ptr<var> clone() const final {
				return std::unique_ptr<var>(new boolean);
			}

		};

		class i8 : virtual public number_var<int8_t> {
		public:
			using value_type = int8_t;
		public:
			i8() {}
			i8(std::string_view name, int8_t value = 0) : number_var<int8_t>(name, value) {}

			std::string_view get_type() const final { return "i8"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new i8()); }
		};

		class i16 : virtual public number_var<int16_t> {
		public:
			using value_type = int16_t;
		public:
			i16() {}
			i16(std::string_view name, int16_t value = 0) : number_var<int16_t>(name, value) {}

			std::string_view get_type() const final { return "i16"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new i16()); }
		};

		class i32 : virtual public number_var<int32_t> {
		public:
			using value_type = int32_t;
		public:
			i32() {}
			i32(std::string_view name, int32_t value = 0) : number_var<int32_t>(name, value) {}

			std::string_view get_type() const final { return "i32"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new i32()); }
		};

		class i64 : virtual public number_var<int64_t> {
		public:
			using value_type = int64_t;
		public:
			i64() {}
			i64(std::string_view name, int value = 0) : number_var<int64_t>(name, value) {}

			std::string_view get_type() const final { return "i64"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new i64()); }
		};

		class u8 : virtual public number_var<uint8_t> {
		public:
			using value_type = uint8_t;
		public:
			u8() {}
			u8(std::string_view name, uint8_t value = 0) : number_var<uint8_t>(name, value) {}

			std::string_view get_type() const final { return "u8"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new u8()); }
		};

		class u16 : virtual public number_var<uint16_t> {
		public:
			using value_type = uint16_t;
		public:
			u16() {}
			u16(std::string_view name, uint16_t value = 0) : number_var<uint16_t>(name, value) {}

			std::string_view get_type() const final { return "u16"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new u16()); }
		};

		class u32 : virtual public number_var<uint32_t> {
		public:
			using value_type = uint32_t;
		public:
			u32() {}
			u32(std::string_view name, uint32_t value = 0) : number_var<uint32_t>(name, value) {}

			std::string_view get_type() const final { return "u32"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new u32()); }
		};

		class u64 : virtual public number_var<uint64_t> {
		public:
			using value_type = uint64_t;
		public:
			u64() {}
			u64(std::string_view name, uint64_t value = 0) : number_var<uint64_t>(name, value) {}

			std::string_view get_type() const final { return "u64"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new u64()); }
		};

		class f32 : virtual public number_var<float> {
		public:
			using value_type = double;
		public:
			f32() {}
			f32(std::string_view name, float value = 0) : number_var<float>(name, value) {}

			std::string_view get_type() const final { return "f32"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new f32()); }
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

		class f96 : virtual public number_var<long double> {
		public:
			using value_type = double;
		public:
			f96() {}
			f96(std::string_view name, long double value = 0) : number_var<long double>(name, value) {}

			std::string_view get_type() const final { return "f96"; }

			std::unique_ptr<var> clone() const final { return std::unique_ptr<var>(new f96()); }
		};
	}
}