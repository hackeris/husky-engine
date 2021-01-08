//
// Created by rainm on 2021/1/3.
//

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

    auto vector_ = args[0].de_ref();

    auto symbols = rt.get_symbols();
    auto default_value = args[1].get<primitive>();
    if (default_value.holds<int>()) {
        default_value = primitive((float) default_value.get<int>());
    }

    for (auto &s: symbols) {
        if (!vector_.contains(s)) {
            vector_.put(s, default_value);
        }
    }
    return vector_;
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

    return value_holder(ss) / value_holder(primitive(n - 1));
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

    vector to_rank = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, to_rank, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = to_rank.get_values();
    }

    int n = vec_values.size();
    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }
    return sum / primitive(n);
}

value_holder func::sum(const runtime &rt, const std::vector<value_holder> &args) {
    vector to_rank = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, to_rank, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = to_rank.get_values();
    }

    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }
    return sum;
}

value_holder func::std(const runtime &rt, const std::vector<value_holder> &args) {

    vector to_rank = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, to_rank, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = to_rank.get_values();
    }

    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }

    int n = vec_values.size();
    auto avg = sum / primitive(n);
    primitive ss(0);
    for (const auto &iter : vec_values) {
        auto delta = (iter.second - avg);
        ss = ss + delta * delta;
    }

    return ss / primitive(n);
}

value_holder func::zscore(const runtime &rt, const std::vector<value_holder> &args) {

    vector to_rank = args[0].de_ref();
    std::map<std::string, primitive> vec_values;
    if (args.size() > 1) {
        auto masked = mask(rt, to_rank, args[1].de_ref());
        vec_values = masked.de_ref().get_values();
    } else {
        vec_values = to_rank.get_values();
    }

    primitive sum(0);
    for (const auto &iter : vec_values) {
        sum = sum + iter.second;
    }

    int n = vec_values.size();
    auto avg = sum / primitive(n);
    primitive ss(0);
    for (const auto &iter : vec_values) {
        auto delta = (iter.second - avg);
        ss = ss + delta * delta;
    }

    auto vec_ = value_holder(vector(std::move(vec_values)));
    auto avg_ = value_holder(avg);
    auto std_ = value_holder((ss / primitive(n)));
    return (vec_ - avg_) / std_;
}
