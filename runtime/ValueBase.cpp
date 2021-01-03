//
// Created by rainm on 2021/1/2.
//
#include "ValueBase.h"
#include <cpprest/json.h>

template<typename T>
web::json::value to_object(const std::map<std::string, PrimitiveValue> &values) {
    using namespace web;
    json::value result = json::value::object();
    for (auto &pair: values) {
        result[pair.first] = json::value::number(pair.second.template get<T>());
    }
    return result;
}

template<bool>
web::json::value to_object(const std::map<std::string, PrimitiveValue> &values) {
    using namespace web;
    json::value result = json::value::object();
    for (auto &pair: values) {
        result[pair.first] = json::value::boolean(pair.second.template get<bool>());
    }
    return result;
}

std::string to_string(const ValueHolder &holder) {

    using namespace web;

    json::value result = json::value::object();
    if (holder.holds<PrimitiveValue>()) {
        const auto &v = holder.get<PrimitiveValue>();
        if (v.holds<int>()) {
            result["type"] = json::value::string("int");
            result["value"] = json::value::number(v.get<int>());
        } else if (v.holds<float>()) {
            result["type"] = json::value::string("float");
            result["value"] = json::value::number(v.get<float>());
        }
    } else if (holder.holds<Vector>()) {
        const auto &v = holder.get<Vector>();
        const auto &values = v.getValues();
        if (!values.empty()) {
            auto iter = values.begin();
            auto ele = (*iter).second;
            if (ele.holds<int>()) {
                result["type"] = json::value::string("vector<int>");
                result["value"] = to_object<int>(values);
            } else if (ele.holds<float>()) {
                result["type"] = json::value::string("vector<float>");
                result["value"] = to_object<float>(values);
            } else if (ele.holds<bool>()) {
                result["type"] = json::value::string("vector<bool>");
                result["value"] = to_object<bool>(values);
            }
        }
    }

    std::stringstream stream;
    result.serialize(stream);

    return stream.str();
}
