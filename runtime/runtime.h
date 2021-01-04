//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_ENGINE_RUNTIME_H
#define HUSKY_ENGINE_RUNTIME_H

#include <map>
#include <string>
#include <optional>
#include <functional>

#include "lang/graph.h"
#include "runtime/value_base.h"
#include "dal/data_repository.h"

namespace husky {

    class runtime;

    using ext_function = std::function<value_holder(
            const runtime &rt,
            const std::vector<value_holder> &)>;

    class runtime {
    public:

        explicit runtime(std::string date,
                         std::shared_ptr<data_repository> repo);

        [[nodiscard]]
        bool has_function(const std::string &name) const;

        [[nodiscard]]
        bool has_identifier(const std::string &name) const;

        [[nodiscard]]
        const ext_function &get_function(const std::string &name) const;

        [[nodiscard]]
        value_holder evaluate(const identifier_ref &identifier) const;

        [[nodiscard]]
        value_holder evaluate(const identifier_ref &identifier, int index) const;

        [[nodiscard]]
        std::set<std::string> get_symbols() const;

    private:
        [[nodiscard]]
        vector wrap(const std::map<std::string, float> &values) const;

    private:
        std::string date;
        std::shared_ptr<data_repository> repo;
        std::map<std::string, ext_function> functions;
        std::map<std::string, std::function<value_holder(const runtime &)>> internal_idents;
    };

}

#endif //HUSKY_ENGINE_RUNTIME_H
