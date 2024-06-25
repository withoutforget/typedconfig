#pragma once

#include <string>
#include <string_view>
#include <memory>

#include "IVar.h"

template <typename T>
T string_view_to(std::string_view sv) {
    T ret{};
    auto result = std::from_chars(sv.data(), sv.data() + sv.size(), ret);
    if (result.ec != std::errc{})
        throw std::runtime_error{
            std::format("Cannot convert '{}' to type '{}'", sv, typeid(T).name()) };
    return ret;

}

namespace TypedConfig {


    template<typename T>
    class NumberVar : public IVar {
    private:
        T m_value;
    protected:
        NumberVar() : IVar(""), m_value(T{}) {}
    public:
        NumberVar(std::string_view name, T value = T{}) : IVar(name), m_value(value) {}
        virtual ~NumberVar() = default;

        virtual std::string_view type_string() const = 0;
        virtual var_t type() const = 0;

        std::string get_value() const override { return std::to_string(m_value); }
        void set_value(std::string_view value) override { m_value = string_view_to<T>(value); }

        virtual std::unique_ptr<IVar> clone() const = 0;
    };

    class i32Var : public NumberVar<__int32> {
    public:
        i32Var() = default;
    public:
        i32Var(std::string_view name, __int32 value = 0) : NumberVar(name, value) {}

        std::string_view type_string() const override { return "i32"; }
        var_t type() const override { return e_i32; }

        std::unique_ptr<IVar> clone() const override { return std::unique_ptr<IVar>(new i32Var()); }
    };

    class f64Var : public NumberVar<double> {
    public:
        f64Var() = default;
    public:
        f64Var(std::string_view name, double value = 0) : NumberVar(name, value) {}

        std::string_view type_string() const override { return "f64"; }
        var_t type() const override { return e_f64; }

        std::unique_ptr<IVar> clone() const override { return std::unique_ptr<IVar>(new f64Var()); }
    };


}