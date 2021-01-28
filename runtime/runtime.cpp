//
// Created by rainm on 2021/1/2.
//

#include <map>
#include <string>
#include "runtime.h"
#include "lib/func.h"

#include <utility>

#include "graph_vm.h"
#include "lang/graph_compiler.h"

using namespace husky;

runtime::runtime(std::string date,
                 std::shared_ptr<data_repository> repo)
        : repo(std::move(repo)), date(std::move(date)) {

    functions.emplace("rank", func::rank);
    functions.emplace("avail", func::avail);
    functions.emplace("avg_t", func::avg_t);
    functions.emplace("sum_t", func::sum_t);
    functions.emplace("max_t", func::max_t);
    functions.emplace("std_t", func::std_t);
    functions.emplace("avg", func::avg);
    functions.emplace("sum", func::sum);
    functions.emplace("std", func::std);
    functions.emplace("max", func::max);
    functions.emplace("zscore", func::zscore);
    functions.emplace("noisy", func::noisy);
    functions.emplace("log", func::log);
    functions.emplace("exp", func::exp);
    functions.emplace("count", func::count);
    functions.emplace("if", func::if_select);
    functions.emplace("sqrt", func::sqrt);
    functions.emplace("drop_false", func::drop_false);

    internal_idents.emplace(
            "all",
            wrap([](const auto &s) -> decltype(auto) {
                return true;
            }));
    internal_idents.emplace(
            "chi_next",
            wrap([](const auto &s) -> decltype(auto) {
                return s[0] == '3';
            }));
    internal_idents.emplace(
            "star",
            wrap([](const auto &s) -> decltype(auto) {
                return (s[0] == '6' && s[1] == '8' && s[2] == '8');
            }));
    internal_idents.emplace(
            "sse",
            wrap([](const auto &s) -> decltype(auto) {
                return s[0] == '6';
            }));
    internal_idents.emplace(
            "sze",
            wrap([](const auto &s) -> decltype(auto) {
                return s[0] == '0' || s[0] == '3';
            }));

    internal_idents.emplace(
            "a50", wrap("rank(circ_mv, !star) <= 50"));
    internal_idents.emplace(
            "csi300", wrap("rank(circ_mv, !star) <= 300"));
    internal_idents.emplace(
            "csi500", wrap("rank(circ_mv, !star) > 300 & rank(circ_mv, !star) <= 800"));
    internal_idents.emplace(
            "csi800", wrap("rank(circ_mv, !star) <= 800"));
    internal_idents.emplace(
            "chi_next_100", wrap("rank(circ_mv, chi_next) <= 100"));
}

bool runtime::has_function(const std::string &name) const {
    return functions.find(name) != functions.end();
}

bool runtime::has_identifier(const std::string &name) const {

    if (internal_idents.find(name) != internal_idents.end()) {
        return true;
    }

    return repo->factor_exists(name);
}

const ext_function &runtime::get_function(const std::string &name) const {
    auto iter = functions.find(name);
    if (iter != functions.end()) {
        return (*iter).second;
    }
    throw std::runtime_error("unexpected identifier " + name);
}

value_holder runtime::evaluate(const identifier_ref &identifier) const {

    if (!has_identifier(identifier.get_name())) {
        throw std::runtime_error("unexpected identifier " + identifier.get_name());
    }

    const std::string &name = identifier.get_name();

    auto internal_iter = internal_idents.find(name);
    if (internal_iter != internal_idents.end()) {
        auto value_getter = (*internal_iter).second;
        return value_getter(*this);
    }

    return vector_ref([this, name](int index) -> vector {
        return to_vector(repo->get_factor_values(name, date, index));
    });
}

value_holder runtime::evaluate(const identifier_ref &identifier, int index) const {

    if (!has_identifier(identifier.get_name())) {
        throw std::runtime_error("unexpected identifier " + identifier.get_name());
    }

    vector_ref ref = evaluate(identifier).get<vector_ref>();
    return vector_ref([ref, index](int offset) -> vector {
        return ref.get(index + offset);
    });
}

vector runtime::to_vector(const std::map<std::string, float> &values) const {
    std::map<std::string, primitive> result;
    for (auto &pair : values) {
        result.emplace(pair.first, primitive((float) pair.second));
    }
    return vector(std::move(result));
}

std::set<std::string> runtime::get_symbols() const {

    auto symbols = repo->get_symbols(date);

    std::set<std::string> result;
    std::copy(symbols.begin(), symbols.end(),
              std::inserter(result, result.end()));
    return result;
}

std::function<value_holder(const runtime &rt)> runtime::wrap(
        const std::function<bool(const std::string &)> &pred) {

    return [pred](const runtime &rt) -> decltype(auto) {
        auto symbols = rt.get_symbols();
        std::map<std::string, primitive> values;
        std::transform(symbols.begin(), symbols.end(),
                       std::inserter(values, values.end()),
                       [&](const std::string &s) -> decltype(auto) {
                           bool val = pred(s);
                           return std::make_pair(s, primitive{val});
                       });
        return value_holder(vector(std::move(values)));
    };
}

std::function<value_holder(const runtime &rt)> runtime::wrap(const std::string &formula) {

    return [formula](const runtime &rt) -> decltype(auto) {
        auto graph = graph_compiler::compile(formula);
        auto new_rt = std::make_shared<runtime>(rt.date, rt.repo);
        graph_vm vm(new_rt);
        return vm.run(graph);
    };
}


