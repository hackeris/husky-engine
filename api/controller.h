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
#include "util/lru_cache.h"

#include <cpprest/json.h>
#include <cpprest/http_listener.h>

#undef U

#include "lang/graph_compiler.h"
#include "dal/value_cache.h"


namespace husky::api {

    using namespace web;
    using namespace ::web::http;

    using husky::data_repository;
    using husky::value_holder;

    class controller {
    public:
        explicit controller(std::shared_ptr<data_repository> dal, std::shared_ptr<value_cache> cache)
                : dal(std::move(dal)), cache_(std::move(cache)) {}

        void compute_post(const http_request &req) const;

        void syntax_check(const http_request &req) const;

        void cache_usage(const http_request &req) const;

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

        static json::value to_json(const std::vector<syntax_error_item> &errors);

    private:
        std::shared_ptr<data_repository> dal;
        std::shared_ptr<value_cache> cache_;
    };
}


#endif //HUSKY_ENGINE_CONTROLLER_H
