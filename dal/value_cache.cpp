//
// Created by rainm on 2021/1/23.
//

#include <memory>

#include "value_cache.h"

using namespace husky;

using husky::cache::cache_key;
using husky::cache::cache_value;
using husky::cache::raw_cached_vector;

value_cache::value_cache(size_t size) : cache_("value_cache", size) {
}

cache_value husky::cache::to_cache(const value_holder &val) {
    if (val.holds<vector>()) {
        auto &v = val.get<vector>();
        cached_vector cv = std::make_shared<raw_cached_vector>();
        (*cv).resize(v.get_values().size());

        int i = 0;
        for (const auto &iter : v.get_values()) {
            auto &el = (*cv)[i];
            strcpy(el.symbol, iter.first.c_str());
            if (iter.second.holds<int>()) {
                el.type = cached_vector_element::type_integer;
                el.value.v_i = iter.second.get<int>();
            } else if (iter.second.holds<float>()) {
                el.type = cached_vector_element::type_float;
                el.value.v_f = iter.second.get<float>();
            } else if (iter.second.holds<bool>()) {
                el.type = cached_vector_element::type_bool;
                el.value.v_b = iter.second.get<bool>();
            }
            i += 1;
        }
        return cv;
    }
    return val;
}

cache_value husky::cache::to_cache(const std::map<std::string, float> &values) {

    cached_vector cv = std::make_shared<raw_cached_vector>();
    cv->resize(values.size());

    int i = 0;
    for (const auto &iter : values) {
        auto &el = (*cv)[i];
        strcpy(el.symbol, iter.first.c_str());
        el.type = cached_vector_element::type_float;
        el.value.v_f = iter.second;
        i += 1;
    }
    return cv;
}

value_holder husky::cache::as_value_holder(const cache_value &cv) {
    if (std::holds_alternative<value_holder>(cv)) {
        return std::get<value_holder>(cv);
    }

    cached_vector v = std::get<cached_vector>(cv);
    std::map<std::string, primitive> result;
    for (auto &el : *v) {
        if (el.type == cached_vector_element::type_float) {
            result.emplace(el.symbol, primitive(el.value.v_f));
        } else if (el.type == cached_vector_element::type_integer) {
            result.emplace(el.symbol, primitive(el.value.v_i));
        } else if (el.type == cached_vector_element::type_bool) {
            result.emplace(el.symbol, primitive(el.value.v_b));
        }
    }
    return vector(std::move(result));
}

std::map<std::string, float> husky::cache::as_values(const cache_value &cv) {

    cached_vector v = std::get<cached_vector>(cv);
    std::map<std::string, float> result;

    for (auto &el : *v) {
        if (el.type == cached_vector_element::type_float) {
            result.emplace(el.symbol, el.value.v_f);
        }
    }
    return result;
}

void value_cache::put(const std::string &formula, const std::string &date, const value_holder &val) {
    using husky::cache::to_cache;
    cache_.put(cache_key{formula, date}, to_cache(val));
}

void value_cache::put(const std::string &formula, const std::string &date, const std::map<std::string, float> &val) {
    using husky::cache::to_cache;
    cache_.put(cache_key{formula, date}, to_cache(val));
}

std::optional<value_holder> value_cache::get_value_holder(const std::string &formula, const std::string &date) {

    using husky::cache::as_value_holder;

    auto maybe_val = cache_.get(cache_key{formula, date});
    if (maybe_val.has_value()) {
        return as_value_holder(maybe_val.value());
    }
    return std::nullopt;
}

std::optional<std::map<std::string, float>>
value_cache::get_values(const std::string &formula, const std::string &date) {

    using husky::cache::as_values;

    auto maybe_val = cache_.get(cache_key{formula, date});
    if (maybe_val.has_value()) {
        return as_values(maybe_val.value());
    }
    return std::nullopt;
}
