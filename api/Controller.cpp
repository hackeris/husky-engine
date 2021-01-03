//
// Created by rainm on 2021/1/3.
//

#include "Controller.h"
#include "runtime/Runtime.h"
#include "runtime/GraphVM.h"
#include "lang/GraphCompiler.h"

#include <cpprest/json.h>

ValueHolder Controller::compute(const std::string &formula, const std::string &date) const {

    auto rt = std::make_shared<Runtime>(date, dal);
    auto graph = GraphCompiler::compile(formula);

    GraphVM gvm(rt);
    return gvm.evaluate(graph);
}

void Controller::compute(const http_request &req) const {

    const auto &params = uri::split_query(req.request_uri().query());
    auto formula = get<std::string>(params, "formula");
    auto date = get<std::string>(params, "date");
    if (!(formula.has_value() && date.has_value())) {
        req.reply(status_codes::BadRequest);
        return;
    }

    auto result = compute(
            from_base64(formula.value()), date.value());
    auto res = to_json(result);
    req.reply(status_codes::OK, res);
}

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

web::json::value to_json(const ValueHolder &holder) {

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

    return result;
}

std::string to_string(const ValueHolder &holder) {

    using namespace web;
    json::value result = to_json(holder);
    std::stringstream stream;
    result.serialize(stream);

    return stream.str();
}

std::string from_base64(const std::string &base64) {

    auto buffer = utility::conversions::from_base64(base64);

    std::ostringstream oss;
    std::copy(buffer.begin(), buffer.end(),
              std::ostream_iterator<unsigned char>(oss));

    return oss.str();
}