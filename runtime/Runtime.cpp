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
    functions.emplace("avail", avail);
    functions.emplace("avg_t", avgT);
}

bool Runtime::hasFunction(const std::string &name) const {
    return functions.find(name) != functions.end();
}

bool Runtime::hasIdentifier(const std::string &name) const {
    return repo->factorExists(name);
}

const Function &Runtime::getFunction(const std::string &name) const {
    auto iter = functions.find(name);
    if (iter != functions.end()) {
        return (*iter).second;
    }
    throw std::runtime_error("unexpected identifier " + name);
}

ValueHolder Runtime::evaluate(const IdentifierRef &identifier) const {

    if (!hasIdentifier(identifier.getName())) {
        throw std::runtime_error("unexpected identifier " + identifier.getName());
    }

    const std::string &name = identifier.getName();
    return VectorRef([this, name](int index) -> Vector {
        return wrap(repo->getFactorValues(name, date, index));
    });
}

ValueHolder Runtime::evaluate(const IdentifierRef &identifier, int index) const {

    if (!hasIdentifier(identifier.getName())) {
        throw std::runtime_error("unexpected identifier " + identifier.getName());
    }

    VectorRef ref = evaluate(identifier).get<VectorRef>();
    return VectorRef([ref, index](int offset) -> Vector {
        return ref.get(index + offset);
    });
}

Vector Runtime::wrap(const std::map<std::string, float> &values) const {
    std::map<std::string, PrimitiveValue> result;
    for (auto &pair : values) {
        result.emplace(pair.first, PrimitiveValue((float) pair.second));
    }
    return Vector(std::move(result));
}

std::set<std::string> Runtime::getSymbols() const {

    auto symbols = repo->getSymbols(date);

    std::set<std::string> result;
    std::copy(symbols.begin(), symbols.end(),
              std::inserter(result, result.end()));
    return result;
}


