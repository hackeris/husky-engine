//
// Created by rainm on 2021/1/3.
//

#include "func.h"

value_holder rank(const runtime &rt, const std::vector<value_holder> &args) {

    auto vectorToRank = args[0].de_ref();
    auto &vec_values = vectorToRank.getValues();

    std::vector<std::pair<std::string, primitive>> values;
    if (args.size() > 1) {
        auto maskVector = args[1].de_ref().as<vector>();
        auto &maskValues = maskVector.getValues();
        std::copy_if(vec_values.begin(), vec_values.end(),
                     std::back_inserter(values),
                     [&maskVector](const auto &p) -> decltype(auto) {
                         if (maskVector.contains(p.first)) {
                             primitive b = maskVector.get(p.first).value();
                             return b.holds<bool>() && b.get<bool>();
                         }
                         return false;
                     });
    } else {
        std::copy(vec_values.begin(), vec_values.end(),
                  std::back_inserter(values));
    }

    std::vector<int> array_index(values.size());
    for (int i = 0; i < values.size(); i++) {
        array_index[i] = i;
    }
    std::sort(array_index.begin(), array_index.end(),
              [&values](int left, int right) -> bool {
                  auto b = values[left].second < values[right].second;
                  return b.get<bool>();
              });

    std::map<std::string, primitive> ranks;
    for (int i = 0; i < values.size(); i++) {
        ranks.emplace(values[i].first, primitive(array_index[i]));
    }
    return vector(std::move(ranks));
}

value_holder avail(const runtime &rt, const std::vector<value_holder> &args) {

    auto vector_ = args[0].de_ref();

    auto symbols = rt.getSymbols();
    auto defaultValue = args[1].get<primitive>();
    if (defaultValue.holds<int>()) {
        defaultValue = primitive((float) defaultValue.get<int>());
    }

    for (auto &s: symbols) {
        if (!vector_.contains(s)) {
            vector_.put(s, defaultValue);
        }
    }
    return vector_;
}

value_holder avg_t(const runtime &rt, const std::vector<value_holder> &args) {

    if (args.size() != 3) {
        throw std::runtime_error("invalid arguments pass to avg_t");
    }

    auto refHolder = args[0];
    if (!refHolder.holds<vector_ref>()) {
        throw std::runtime_error("invalid arguments pass to avg_t");
    }

    const auto &ref = refHolder.get<vector_ref>();

    int begin = args[1].get<primitive>().get<int>();
    int end = args[2].get<primitive>().get<int>();

    vector vec;
    for (int i = begin; i <= end; i++) {
        if (i == begin) {
            vec = ref.get(i);
        } else {
            vec = vec + ref.get(i);
        }
    }

    return value_holder(vec) / value_holder(primitive(end - begin + 1));
}

value_holder drop_false(const runtime &rt, const std::vector<value_holder> &args) {

    auto sourceVec = args[0].de_ref();

    vector vec;
    const auto &values = sourceVec.getValues();
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