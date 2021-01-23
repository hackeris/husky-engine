//
// Created by rainm on 2021/1/23.
//

#ifndef HUSKY_ENGINE_VALUE_CACHE_H
#define HUSKY_ENGINE_VALUE_CACHE_H

#include <memory>
#include <optional>
#include <vector>
#include <utility>
#include <map>
#include <string>

#include "runtime/value_base.h"
#include "util/lru_cache.h"

namespace husky::cache {
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

    cache_value to_cache(const std::map<std::string, float> &val);

    value_holder as_value_holder(const cache_value &cv);

    std::map<std::string, float> as_values(const cache_value &cv);
}

namespace std {
    template<>
    struct hash<husky::cache::cache_key> {
        std::size_t operator()(husky::cache::cache_key const &s) const noexcept {
            return s.hash();
        }
    };
}

class value_cache {

    using value_holder = husky::value_holder;

public:
    using cache_key = husky::cache::cache_key;
    using cache_value = husky::cache::cache_value;

public:

    value_cache(size_t size);

    void put(const std::string &formula, const std::string &date, const value_holder &val);

    void put(const std::string &formula, const std::string &date, const std::map<std::string, float> &val);

    std::optional<value_holder> get_value_holder(const std::string &formula, const std::string &date);

    std::optional<std::map<std::string, float>> get_values(const std::string &formula, const std::string &date);

    [[nodiscard]]
    inline size_t size() const {
        return cache_.size();
    }

    [[nodiscard]]
    inline size_t used() const {
        return cache_.used();
    }

private:
    lru_cache<cache_key, cache_value> cache_;
};


#endif //HUSKY_ENGINE_VALUE_CACHE_H
