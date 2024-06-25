#pragma once

#include <vector>
#include <memory>


#include "formatter.h"
#include "VarManager.h"
#include "IVar.h"

namespace TypedConfig {

    class Config {
    private:
        std::vector<std::unique_ptr<IVar>> m_data;
        std::unique_ptr<Formatter> m_formatter{ new Formatter() };
    public:
        template<typename T>
        void append(T&& param) {
            m_data.emplace_back(new T(std::forward<T>(param)));
        }

        void append(std::unique_ptr<IVar>&& var) {
            m_data.emplace_back(std::move(var));
        }

        IVar* search(std::string_view name) const {
            for (auto&& el : m_data) {
                if (el->get_name() == name)
                    return el.get();
            }
            return nullptr;
        }

        void set_formatter(const Formatter& formatter) {
            m_formatter.reset(new Formatter(formatter));
        }

        std::string dump() const {
            std::string out{};
            for (auto&& el : m_data)
                out += el->dump(*m_formatter) + "\n";
            return out;
        }

        template<typename Stream>
        void dump_to(Stream& stream) const {
            for (auto&& el : m_data) {
                stream << el->dump(*m_formatter) << '\n';
            }
        }

        template<typename Stream>
        void from_stream(Stream& stream) {
            std::string tmp;
            while (std::getline(stream, tmp)) {
                if (tmp.empty()) continue;
                auto&& [type, name, value] = m_formatter->deserialize(tmp);
                append(VarManager::construct_by(type, name, value));
            }
        }
    };

}