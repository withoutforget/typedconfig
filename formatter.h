#pragma once

#include <string>
#include <format>
#include <string_view>
#include <tuple>

namespace TypedConfig {
class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string serialize(std::string_view type, std::string_view name, std::string_view value) const {
        return std::format("{}:{}={}", type, name, value);
    }
    virtual std::tuple<std::string_view, std::string_view, std::string_view> deserialize(std::string_view inp) const {
        auto colon_pos = inp.find(':');
        auto eq_pos = inp.find('=');
        if (colon_pos == std::string_view::npos || eq_pos == std::string_view::npos || colon_pos > eq_pos)
            throw std::runtime_error{std::format("Error while parsing line '{}' with equal or colon characer", inp)};
        auto type = inp.substr(0, colon_pos);
        auto name = inp.substr(colon_pos + 1, eq_pos - colon_pos - 1);
        auto value = inp.substr(eq_pos + 1);
        if (type.empty() || name.empty() || value.empty())
            throw std::runtime_error{"parse err"};
        return { type, name, value };
    }
};
}