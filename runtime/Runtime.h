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

using Function = std::function<ValueHolder(const std::vector<ValueHolder> &)>;

class Runtime {
public:

    explicit Runtime(std::string date,
                     std::shared_ptr<DataRepository> repo);

    bool hasFunction(const std::string &name);

    bool hasIdentifier(const std::string &name);

    const Function &getFunction(const std::string &name);

    ValueHolder evaluate(const IdentifierRef &identifier);

    ValueHolder evaluate(const IdentifierRef &identifier, int index);

private:
    Vector wrap(const std::map<std::string, float> &values);

private:
    std::string date;
    std::shared_ptr<DataRepository> repo;
    std::map<std::string, Function> functions;
};


#endif //HUSKY_COMPUTE_RUNTIME_H
