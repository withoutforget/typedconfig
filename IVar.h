#pragma once

#include <string>
#include <string_view>
#include <memory>

#include "formatter.h"

namespace TypedConfig {

    enum var_t : unsigned char {
        null,
        e_i32,
        e_f64,
    };

    class IVar {
    protected:
        std::string m_name;
    public:
        IVar(std::string_view name) : m_name(name) {}
        virtual ~IVar() = default;

        virtual std::string_view type_string() const = 0;
        virtual var_t type() const = 0;

        virtual std::string get_value() const = 0;
        virtual void set_value(std::string_view) = 0;

        virtual std::string_view get_name() const { return m_name; }
        virtual void set_name(std::string_view name) { m_name = name; }

        virtual std::string dump(const Formatter& formatter) const {
            return formatter.serialize(type_string(), get_name(), get_value());
        }

        virtual std::unique_ptr<IVar> clone() const = 0;
    };

}