//
// Created by rainm on 2021/1/9.
//

#ifndef HUSKY_ENGINE_LRU_CACHE_H
#define HUSKY_ENGINE_LRU_CACHE_H

#include <list>
#include <mutex>
#include <optional>
#include <unordered_map>

template<typename K, typename V>
class lru_cache {
public:
    explicit lru_cache(size_t size) : size_(size) {}

    void put(const K &k, const V &v) {

        std::lock_guard<std::mutex> lk(mtx_);

        auto p = cache_.find(k);
        if (p != cache_.end()) {
            keys_.erase(p->second.iter);
        } else {
            if (keys_.size() >= size_) {
                cache_.erase(keys_.back());
                keys_.pop_back();
            }
        }

        keys_.push_front(k);
        cache_.emplace(k, lru_entry{keys_.begin(), v});
    }

    std::optional<V> get(const K &k) {

        std::lock_guard<std::mutex> lk(mtx_);

        auto p = cache_.find(k);
        if (p == cache_.end()) {
            return std::nullopt;
        }

        keys_.erase(p->second.iter);

        keys_.push_front(k);
        p->second.iter = keys_.begin();

        return std::make_optional(p->second.value);
    }

private:
    using key_iter = typename std::list<K>::iterator;

    struct lru_entry {
        key_iter iter;
        V value;
    };

    size_t size_;
    std::list<K> keys_;
    std::unordered_map<K, lru_entry> cache_;
    std::mutex mtx_;
};

#endif //HUSKY_ENGINE_LRU_CACHE_H
