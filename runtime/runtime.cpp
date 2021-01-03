//
// Created by rainm on 2021/1/2.
//

#include <map>
#include <string>
#include "runtime.h"
#include "lib/func.h"

#include <utility>

runtime::runtime(std::string date,
                 std::shared_ptr<data_repository> repo)
        : repo(std::move(repo)), date(std::move(date)) {

    functions.emplace("rank", rank);
    functions.emplace("avail", avail);
    functions.emplace("avg_t", avg_t);
    functions.emplace("std_t", std_t);
    functions.emplace("drop_false", drop_false);
}

bool runtime::has_function(const std::string &name) const {
    return functions.find(name) != functions.end();
}

bool runtime::hasIdentifier(const std::string &name) const {
    return repo->factor_exists(name);
}

const Function &runtime::get_function(const std::string &name) const {
    auto iter = functions.find(name);
    if (iter != functions.end()) {
        return (*iter).second;
    }
    throw std::runtime_error("unexpected identifier " + name);
}

value_holder runtime::evaluate(const identifier_ref &identifier) const {

    if (!hasIdentifier(identifier.get_name())) {
        throw std::runtime_error("unexpected identifier " + identifier.get_name());
    }

    const std::string &name = identifier.get_name();
    return vector_ref([this, name](int index) -> vector {
        return wrap(repo->get_factor_values(name, date, index));
    });
}

value_holder runtime::evaluate(const identifier_ref &identifier, int index) const {

    if (!hasIdentifier(identifier.get_name())) {
        throw std::runtime_error("unexpected identifier " + identifier.get_name());
    }

    vector_ref ref = evaluate(identifier).get<vector_ref>();
    return vector_ref([ref, index](int offset) -> vector {
        return ref.get(index + offset);
    });
}

vector runtime::wrap(const std::map<std::string, float> &values) const {
    std::map<std::string, primitive> result;
    for (auto &pair : values) {
        result.emplace(pair.first, primitive((float) pair.second));
    }
    return vector(std::move(result));
}

std::set<std::string> runtime::getSymbols() const {

    auto symbols = repo->get_symbols(date);

    std::set<std::string> result;
    std::copy(symbols.begin(), symbols.end(),
              std::inserter(result, result.end()));
    return result;
}

