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

namespace husky::api {
    struct cache_key {
        std::string formula;
        std::string date;
    public:
        [[nodiscard]]
        std::size_t hash() const {
            std::size_t h1 = std::hash<std::string>{}(formula);
            std::size_t h2 = std::hash<std::string>{}(date);
            return h1 ^ (h2 << 1);
        }

        friend bool operator==(const cache_key &left, const cache_key &right) {
            return left.formula == right.formula
                   && left.date == right.date;
        }
    };

    struct cached_vector_element {
        char symbol[7];
        char type;
        union {
            float v_f;
            int v_i;
            bool v_b;
        } value;

        static constexpr char type_float = 0;
        static constexpr char type_integer = 1;
        static constexpr char type_bool = 2;
    };

    using raw_cached_vector = std::vector<cached_vector_element>;
    using cached_vector = std::shared_ptr<raw_cached_vector>;

    using cache_value = std::variant<cached_vector, value_holder>;

    cache_value to_cache(const value_holder &val);

    value_holder from_cache(const cache_value &cv);
}

namespace std {
    template<>
    struct hash<husky::api::cache_key> {
        std::size_t operator()(husky::api::cache_key const &s) const noexcept {
            return s.hash();
        }
    };
}

namespace husky::api {

    using namespace web;
    using namespace ::web::http;

    using husky::data_repository;
    using husky::value_holder;

    class controller {
    public:
        explicit controller(std::shared_ptr<data_repository> dal, size_t cache_size)
                : dal(std::move(dal)), cache_("value_cache", cache_size) {}

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
        lru_cache<cache_key, cache_value> cache_;
    };
}


#endif //HUSKY_ENGINE_CONTROLLER_H
