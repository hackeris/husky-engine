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

class runtime;

using Function = std::function<value_holder(
        const runtime &rt,
        const std::vector<value_holder> &)>;

class runtime {
public:

    explicit runtime(std::string date,
                     std::shared_ptr<data_repository> repo);

    [[nodiscard]]
    bool has_function(const std::string &name) const;

    [[nodiscard]]
    bool hasIdentifier(const std::string &name) const;

    [[nodiscard]]
    const Function &get_function(const std::string &name) const;

    [[nodiscard]]
    value_holder evaluate(const identifier_ref &identifier) const;

    [[nodiscard]]
    value_holder evaluate(const identifier_ref &identifier, int index) const;

    [[nodiscard]]
    std::set<std::string> getSymbols() const;

private:
    [[nodiscard]]
    vector wrap(const std::map<std::string, float> &values) const;

private:
    std::string date;
    std::shared_ptr<data_repository> repo;
    std::map<std::string, Function> functions;
};


#endif //HUSKY_ENGINE_RUNTIME_H
