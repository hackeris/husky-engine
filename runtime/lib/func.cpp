//
// Created by rainm on 2021/1/3.
//

#include <random>
#include <cmath>

#include "func.h"
#include "util/timer.h"

using namespace husky;

value_holder func::rank(const runtime &rt, const std::vector<value_holder> &args) {

    vector to_rank = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, to_rank, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = to_rank.get_values();
    }

    std::vector<std::pair<std::string, primitive>> values;
    std::copy(vec_values.begin(), vec_values.end(),
              std::back_inserter(values));

    std::sort(values.begin(), values.end(),
              [](const auto &left, const auto &right) -> bool {
                  primitive b = left.second >= right.second;
                  return b.get<bool>();
              });

    std::map<std::string, primitive> ranks;
    for (int i = 0; i < values.size(); i++) {
        ranks.emplace(values[i].first, primitive(i + 1));
    }
    return vector(std::move(ranks));
}

value_holder func::avail(const runtime &rt, const std::vector<value_holder> &args) {

    auto holder = args[0];
    auto default_value = args[1].get<primitive>();
    return avail_(rt, holder, default_value);
}

value_holder func::avg_t(const runtime &rt, const std::vector<value_holder> &args) {

    if (args.size() != 3) {
        throw std::runtime_error("invalid arguments pass to avg_t");
    }

    auto maybe_ref = args[0];
    if (!maybe_ref.holds<vector_ref>()) {
        throw std::runtime_error("invalid arguments pass to avg_t");
    }

    const auto &ref = maybe_ref.get<vector_ref>();

    int begin = args[1].get<primitive>().get<int>();
    int end = args[2].get<primitive>().get<int>();

    std::vector<vector> frames;
    for (int i = begin; i <= end; i++) {
        frames.emplace_back(ref.get(i));
    }

    auto_timer tmr("avg_t on " + std::to_string(end - begin + 1) + " frames");

    vector sum;
    for (int i = 0; i < frames.size(); i++) {
        if (i == 0) {
            sum = frames[i];
        } else {
            sum = sum + frames[i];
        }
    }

    return value_holder(sum) / value_holder(primitive(end - begin + 1));
}

value_holder func::sum_t(const runtime &rt, const std::vector<value_holder> &args) {
    if (args.size() != 3) {
        throw std::runtime_error("invalid arguments pass to sum_t");
    }

    auto maybe_ref = args[0];
    if (!maybe_ref.holds<vector_ref>()) {
        throw std::runtime_error("invalid arguments pass to sum_t");
    }

    const auto &ref = maybe_ref.get<vector_ref>();

    int begin = args[1].get<primitive>().get<int>();
    int end = args[2].get<primitive>().get<int>();

    std::vector<vector> frames;
    for (int i = begin; i <= end; i++) {
        auto el = ref.get(i);
        frames.emplace_back(el);
    }

    auto_timer tmr("sum_t on " + std::to_string(end - begin + 1) + " frames");

    vector sum;
    for (int i = 0; i < frames.size(); i++) {
        if (i == 0) {
            sum = frames[i];
        } else {
            sum = sum + frames[i];
        }
    }

    return value_holder(sum);
}

value_holder func::std_t(const runtime &rt, const std::vector<value_holder> &args) {

    if (args.size() != 3) {
        throw std::runtime_error("invalid arguments pass to std_t");
    }

    auto maybe_ref = args[0];
    if (!maybe_ref.holds<vector_ref>()) {
        throw std::runtime_error("invalid arguments pass to std_t");
    }

    const auto &ref = maybe_ref.get<vector_ref>();

    int begin = args[1].get<primitive>().get<int>();
    int end = args[2].get<primitive>().get<int>();

    std::vector<vector> frames;
    for (int i = begin; i <= end; i++) {
        frames.emplace_back(ref.get(i));
    }

    auto_timer tmr("std_t on " + std::to_string(end - begin + 1) + " frames");

    vector sum;
    for (int i = 0; i < frames.size(); i++) {
        if (i == 0) {
            sum = frames[i];
        } else {
            sum = sum + frames[i];
        }
    }

    float n = (float) end - (float) begin + 1.0f;
    auto avg = (value_holder(sum) / value_holder(primitive(n))).get<vector>();

    vector ss;
    for (int i = 0; i < frames.size(); i++) {
        vector it = frames[i] - avg;
        if (i == 0) {
            ss = it * it;
        } else {
            ss = ss + it * it;
        }
    }

    return sqrt_(value_holder(ss) / value_holder(primitive(n - 1)));
}

value_holder func::drop_false(const runtime &rt, const std::vector<value_holder> &args) {

    auto sourceVec = args[0].de_ref();

    vector vec;
    const auto &values = sourceVec.get_values();
    for (auto &pair:values) {
        if (pair.second.holds<bool>()) {
            if (!pair.second.get<bool>()) {
                continue;
            }
        }
        vec.put(pair.first, pair.second);
    }
    return vec;
}

value_holder func::mask(const runtime &rt, const vector &v, const vector &mask_vec) {

    std::map<std::string, primitive> values;
    auto &mask_values = mask_vec.get_values();
    auto &vec_values = v.get_values();
    std::copy_if(vec_values.begin(), vec_values.end(),
                 std::inserter(values, values.end()),
                 [&mask_vec](const auto &p) -> decltype(auto) {
                     if (mask_vec.contains(p.first)) {
                         primitive b = mask_vec.get(p.first).value();
                         return b.holds<bool>() && b.get<bool>();
                     }
                     return false;
                 });

    return vector(std::move(values));
}

value_holder func::avg(const runtime &rt, const std::vector<value_holder> &args) {

    vector vec = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, vec, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = vec.get_values();
    }

    int n = vec_values.size();
    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }
    return sum / primitive(n);
}

value_holder func::sum(const runtime &rt, const std::vector<value_holder> &args) {
    vector vec = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, vec, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = vec.get_values();
    }

    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }
    return sum;
}

value_holder func::std(const runtime &rt, const std::vector<value_holder> &args) {

    vector vec = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, vec, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = vec.get_values();
    }

    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }

    float n = vec_values.size();
    auto avg = sum / primitive(n);
    primitive ss(0);
    for (const auto &iter : vec_values) {
        auto delta = (iter.second - avg);
        ss = ss + delta * delta;
    }

    return primitive{(float) ::sqrt((ss / primitive(n)).get<float>())};
}

value_holder func::zscore(const runtime &rt, const std::vector<value_holder> &args) {

    vector vec = args[0].de_ref();
    primitive cap = args[2].get<primitive>();

    auto masked = mask(rt, vec, args[1].de_ref());
    std::map<std::string, primitive> vec_values = masked.de_ref().get_values();

    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }

    float n = vec_values.size();
    auto avg = sum / primitive(n);
    primitive ss(0);
    for (const auto &iter : vec_values) {
        auto delta = (iter.second - avg);
        ss = ss + delta * delta;
    }

    auto vec_ = value_holder{vector{std::move(vec_values)}};
    auto avg_ = value_holder{avg};
    auto std_ = primitive{(float) ::sqrt((ss / primitive(n)).get<float>())};

    auto new_vec = (vec_ - avg_) / value_holder{std_};
    vector capped = new_vec.get<vector>();
    capped.broadcast([&cap](primitive &v) {
        if ((v > cap).get<bool>()) {
            v = cap;
        } else if ((v < -cap).get<bool>()) {
            v = -cap;
        }
    });
    return capped;
}

value_holder func::noisy(const runtime &rt, const std::vector<value_holder> &args) {

    vector vec = args[0].de_ref();
    std::map<std::string, primitive> vec_values = vec.get_values();

    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }
    float n = vec_values.size();
    auto avg = sum / primitive(n);
    primitive ss(0);
    for (const auto &iter : vec_values) {
        auto delta = (iter.second - avg);
        ss = ss + delta * delta;
    }

    auto std = primitive{(float) ::sqrt((ss / primitive(n)).get<float>())};

    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::normal_distribution<> d{0.0f, 1.0f};

    auto c = args[1].get<primitive>();
    for (auto &iter : vec_values) {
        iter.second = (iter.second) + c * std * primitive((float) d(gen));
    }
    return vector(std::move(vec_values));
}

value_holder func::log(const runtime &rt, const std::vector<value_holder> &args) {

    vector vec = args[0].de_ref();
    std::map<std::string, primitive> vec_values = vec.get_values();

    std::map<std::string, primitive> log_values;
    std::copy_if(vec_values.begin(), vec_values.end(),
                 std::inserter(log_values, log_values.end()),
                 [](const auto &el) -> decltype(auto) {
                     auto b = el.second > primitive(0);
                     return b.template get<bool>();
                 });

    std::for_each(log_values.begin(), log_values.end(),
                  [](auto &p) {
                      p.second = primitive{(float) ::log(p.second.template get<float>())};
                  });
    return vector(std::move(log_values));
}

value_holder func::exp(const runtime &rt, const std::vector<value_holder> &args) {

    vector vec = args[0].de_ref();
    std::map<std::string, primitive> vec_values = vec.get_values();

    std::for_each(vec_values.begin(), vec_values.end(),
                  [](auto &p) {
                      p.second = primitive{(float) ::exp(p.second.template get<float>())};
                  });
    return vector(std::move(vec_values));
}

value_holder func::sqrt(const runtime &rt, const std::vector<value_holder> &args) {

    return func::sqrt_(args[0]);
}

value_holder func::sqrt_(const value_holder &arg) {

    vector vec = arg.de_ref();
    std::map<std::string, primitive> vec_values = vec.get_values();

    std::map<std::string, primitive> log_values;
    std::copy_if(vec_values.begin(), vec_values.end(),
                 std::inserter(log_values, log_values.end()),
                 [](const auto &el) -> decltype(auto) {
                     auto b = el.second > primitive(0);
                     return b.template get<bool>();
                 });

    std::for_each(log_values.begin(), log_values.end(),
                  [](auto &p) {
                      p.second = primitive{(float) ::sqrt(p.second.template get<float>())};
                  });
    return vector(std::move(log_values));
}

value_holder func::avail_(const runtime &rt, const value_holder &holder, const primitive &default_value) {

    auto default_value_ = default_value;
    if (default_value_.holds<int>()) {
        default_value_ = primitive((float) default_value.get<int>());
    }

    if (holder.holds<vector>()) {
        auto symbols = rt.get_symbols();
        auto vector_ = holder.de_ref();
        for (auto &s: symbols) {
            if (!vector_.contains(s)) {
                vector_.put(s, default_value_);
            }
        }
        return vector_;
    } else {
        return vector_ref([default_value_, &rt, holder](int idx) -> vector {
            auto vec = holder.get<vector_ref>().get(idx);
            return avail_(rt, value_holder{vec}, default_value_).get<vector>();
        });
    }
}
