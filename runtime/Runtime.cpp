//
// Created by rainm on 2021/1/2.
//

#include <map>
#include <string>
#include "Runtime.h"
#include "lib/Function.h"

#include <utility>

Runtime::Runtime(std::string date,
                 std::shared_ptr<DataRepository> repo)
        : repo(std::move(repo)), date(std::move(date)) {

    functions.emplace("rank", rank);
}

bool Runtime::hasFunction(const std::string &name) {
    return functions.find(name) != functions.end();
}

bool Runtime::hasIdentifier(const std::string &name) {
    return repo->factorExists(name);
}

const Function &Runtime::getFunction(const std::string &name) {
    return functions[name];
}

ValueHolder Runtime::evaluate(const IdentifierRef &identifier) {

    if (!hasIdentifier(identifier.getName())) {
        throw std::runtime_error("unexpected identifier " + identifier.getName());
    }

    const std::string &name = identifier.getName();
    return VectorRef([this, name](int index) -> Vector {
        return wrap(repo->getFactorValues(name, date, index));
    });
}

ValueHolder Runtime::evaluate(const IdentifierRef &identifier, int index) {

    if (!hasIdentifier(identifier.getName())) {
        throw std::runtime_error("unexpected identifier " + identifier.getName());
    }

    VectorRef ref = evaluate(identifier).get<VectorRef>();
    return VectorRef([ref, index](int offset) -> Vector {
        return ref.get(index + offset);
    });
}

Vector Runtime::wrap(const std::map<std::string, float> &values) {
    std::map<std::string, PrimitiveValue> result;
    for (auto &pair : values) {
        result.emplace(pair.first, PrimitiveValue((float) pair.second));
    }
    return Vector(std::move(result));
}


