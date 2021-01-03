//
// Created by rainm on 2021/1/3.
//

#include "Function.h"

ValueHolder rank(const Runtime &runtime, const std::vector<ValueHolder> &args) {

    auto vectorToRank = args[0].deRef();
    auto &vectorValues = vectorToRank.getValues();

    std::vector<std::pair<std::string, PrimitiveValue>> values;
    if (args.size() > 1) {
        auto maskVector = args[1].deRef().as<Vector>();
        auto &maskValues = maskVector.getValues();
        std::copy_if(vectorValues.begin(), vectorValues.end(),
                     std::back_inserter(values),
                     [&maskVector](const auto &p) -> decltype(auto) {
                         if (maskVector.contains(p.first)) {
                             PrimitiveValue b = maskVector.get(p.first).value();
                             return b.holds<bool>() && b.get<bool>();
                         }
                         return false;
                     });
    } else {
        std::copy(vectorValues.begin(), vectorValues.end(),
                  std::back_inserter(values));
    }

    std::vector<int> arrayIndex(values.size());
    for (int i = 0; i < values.size(); i++) {
        arrayIndex[i] = i;
    }
    std::sort(arrayIndex.begin(), arrayIndex.end(),
              [&values](int left, int right) -> bool {
                  auto b = values[left].second < values[right].second;
                  return b.get<bool>();
              });

    std::map<std::string, PrimitiveValue> ranks;
    for (int i = 0; i < values.size(); i++) {
        ranks.emplace(values[i].first, PrimitiveValue(arrayIndex[i]));
    }
    return Vector(std::move(ranks));
}

ValueHolder avail(const Runtime &runtime, const std::vector<ValueHolder> &args) {

    auto vector = args[0].deRef();

    auto symbols = runtime.getSymbols();
    auto defaultValue = args[1].get<PrimitiveValue>();
    if (defaultValue.holds<int>()) {
        defaultValue = PrimitiveValue((float) defaultValue.get<int>());
    }

    for (auto &s: symbols) {
        if (!vector.contains(s)) {
            vector.put(s, defaultValue);
        }
    }
    return vector;
}

ValueHolder avgT(const Runtime &runtime, const std::vector<ValueHolder> &args) {

    if (args.size() != 3) {
        throw std::runtime_error("invalid arguments pass to avg_t");
    }

    auto refHolder = args[0];
    if (!refHolder.hold<VectorRef>()) {
        throw std::runtime_error("invalid arguments pass to avg_t");
    }

    const auto &ref = refHolder.get<VectorRef>();

    int begin = args[1].get<PrimitiveValue>().get<int>();
    int end = args[2].get<PrimitiveValue>().get<int>();

    Vector vec;
    for (int i = begin; i <= end; i++) {
        if (i == begin) {
            vec = ref.get(i);
        } else {
            vec = vec + ref.get(i);
        }
    }

    return ValueHolder(vec) / ValueHolder(PrimitiveValue(end - begin + 1));
}