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

#include "runtime/value_base.h"
#include "dal/data_repository.h"

#include <cpprest/json.h>
#include <cpprest/http_listener.h>


#undef U

namespace husky::api {

    using namespace web;
    using namespace ::web::http;

    using husky::data_repository;
    using husky::value_holder;

    class controller {
    public:
        explicit controller(std::shared_ptr<data_repository> dal) : dal(std::move(dal)) {}

        void compute_get(const http_request &req) const;

        void compute_post(const http_request &req) const;

    private:
        [[nodiscard]]
        value_holder compute(const std::string &formula, const std::string &date) const;

        template<typename K, typename V>
        static std::optional<V> get(const std::map<K, V> &m, const K &k) {
            auto iter = m.find(k);
            if (iter == m.end()) {
                return std::nullopt;
            }

            return (*iter).second;
        }

        static json::value to_json(const std::string &formula, const std::string &date, const value_holder &holder);

        static std::string from_base64(const std::string &base64);

    private:

        std::shared_ptr<data_repository> dal;
    };
}

#endif //HUSKY_ENGINE_CONTROLLER_H
