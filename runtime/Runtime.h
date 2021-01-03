//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_COMPUTE_RUNTIME_H
#define HUSKY_COMPUTE_RUNTIME_H

#include <map>
#include <string>
#include <optional>
#include <functional>

#include "lang/Graph.h"
#include "runtime/ValueBase.h"
#include "dal/DataRepository.h"

class Runtime;

using Function = std::function<ValueHolder(
        const Runtime &runtime,
        const std::vector<ValueHolder> &)>;

class Runtime {
public:

    explicit Runtime(std::string date,
                     std::shared_ptr<DataRepository> repo);

    [[nodiscard]]
    bool hasFunction(const std::string &name) const;

    [[nodiscard]]
    bool hasIdentifier(const std::string &name) const;

    [[nodiscard]]
    const Function &getFunction(const std::string &name) const;

    [[nodiscard]]
    ValueHolder evaluate(const IdentifierRef &identifier) const;

    [[nodiscard]]
    ValueHolder evaluate(const IdentifierRef &identifier, int index) const;

    [[nodiscard]]
    std::set<std::string> getSymbols() const;

private:
    [[nodiscard]]
    Vector wrap(const std::map<std::string, float> &values) const;

private:
    std::string date;
    std::shared_ptr<DataRepository> repo;
    std::map<std::string, Function> functions;
};


#endif //HUSKY_COMPUTE_RUNTIME_H
