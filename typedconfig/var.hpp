#pragma once
#include <string_view>
#include <memory>
#include <concepts>

#include "formatter.h"


#include "utils.hpp"

namespace typedconfig {
	/* interface for any config variable */
	class var {
	public:
		virtual ~var() = default;
		
		// getters
		virtual std::string_view get_type() const = 0;
		virtual std::string_view get_name() const = 0;
		virtual std::string get_value() const = 0;
		// setters
		virtual void set_name(std::string_view) = 0;
		virtual void set_value(std::string_view) = 0;

		// input/output
		virtual std::string dump(const formatter& formatter) const {
			return formatter.serialize(get_type(), get_name(), get_value());
		}

		// clone
		virtual std::unique_ptr<var> clone() const = 0;
	};
}