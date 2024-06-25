#pragma once

#include <vector>
#include <memory>
#include <string_view>

#include "IVar.h"
#include "NumberVar.h"

namespace TypedConfig {
    class VarManager {
    private:
        std::vector<IVar*> m_types;
        VarManager() = default;
    public:
        static VarManager& instance() {
            static VarManager vt;
            vt.import_type<i32Var>();
            vt.import_type<f64Var>();
            return vt;
        }

        template<typename T>
        void import_type() {
            m_types.emplace_back(new T{});
        }

        std::unique_ptr<IVar> create(std::string_view type_string) const {
            for (auto p : m_types) {
                if (p->type_string() == type_string)
                    return p->clone();
            }
            return {};
        }

        std::unique_ptr<IVar> create(var_t type) const {
            for (auto p : m_types) {
                if (p->type() == type)
                    return p->clone();
            }
            return {};
        }

        static std::unique_ptr<IVar> construct_by(std::string_view type, std::string_view name, std::string_view value) {
            auto& vm = VarManager::instance();
            auto var = vm.create(type);
            var->set_name(name);
            var->set_value(value);
            return var;
        }

    };
}