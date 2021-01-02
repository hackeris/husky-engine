//
// Created by rainm on 2021/1/3.
//

#include "Function.h"

ValueHolder rank(const std::vector<ValueHolder> &args) {

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
                             const PrimitiveValue &b = maskVector.get(p.first).value();
                             return b.valueIs<bool>() && b.get<bool>();
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
