//
// Created by rainm on 2021/1/3.
//

#ifndef HUSKY_ENGINE_CONTROLLER_H
#define HUSKY_ENGINE_CONTROLLER_H

#include <memory>
#include <optional>
#include <utility>
#include <map>
#include <string>

#include "runtime/ValueBase.h"
#include "dal/DataRepository.h"

#include <cpprest/json.h>
#include <cpprest/http_listener.h>

using namespace web;
using namespace web::http;

#undef U

class Controller {
public:
    explicit Controller(std::shared_ptr<DataRepository> dal) : dal(std::move(dal)) {}

    void compute(const http_request &req) const;

private:
    [[nodiscard]]
    ValueHolder compute(const std::string &formula, const std::string &date) const;

    template<typename K, typename V>
    static std::optional<V> get(const std::map<K, V> &m, const K &k) {
        auto iter = m.find(k);
        if (iter == m.end()) {
            return std::nullopt;
        }

        return (*iter).second;
    }

private:

    std::shared_ptr<DataRepository> dal;
};

web::json::value to_json(const ValueHolder &holder);

std::string to_string(const ValueHolder &holder);

std::string from_base64(const std::string &base64);

#endif //HUSKY_ENGINE_CONTROLLER_H
