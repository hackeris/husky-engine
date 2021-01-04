//
// Created by rainm on 2021/1/3.
//

#include "controller.h"
#include "runtime/runtime.h"
#include "runtime/graph_vm.h"
#include "lang/graph_compiler.h"

#include <cpprest/json.h>
#include "util/timer.h"

using namespace husky;
using namespace husky::api;

value_holder controller::compute(const std::string &formula, const std::string &date) const {

    auto rt = std::make_shared<runtime>(date, dal);
    auto graph = graph_compiler::compile(formula);

    graph_vm gvm(rt);
    return gvm.evaluate(graph);
}

void controller::compute_get(const http_request &req) const {

    const auto &params = uri::split_query(req.request_uri().query());
    auto encoded_formula = get<std::string>(params, "formula");
    auto date = get<std::string>(params, "date");
    if (!(encoded_formula.has_value() && date.has_value())) {
        req.reply(status_codes::BadRequest);
        return;
    }

    auto formula = from_base64(encoded_formula.value());

    auto_timer tmr("compute values of '" + formula + "' at " + date.value());

    auto result = compute(formula, date.value());
    auto res = to_json(result);
    req.reply(status_codes::OK, res);
}

void controller::compute_post(const http_request &req) const {

    using concurrency::streams::stringstreambuf;

    stringstreambuf buffer;
    req.body().read_to_end(buffer).wait();
    std::string content = buffer.collection();

    json::value body = json::value::parse(content);

    auto formula = body["formula"].as_string();
    auto date = body["date"].as_string();

    auto_timer tmr("compute values of '" + formula + "' at " + date);

    auto result = compute(formula, date);
    auto res = to_json(result);
    req.reply(status_codes::OK, res);
}

template<typename T>
web::json::value to_object(const std::map<std::string, primitive> &values) {
    using namespace web;
    json::value result = json::value::object();
    for (auto &pair: values) {
        result[pair.first] = json::value::number(pair.second.template get<T>());
    }
    return result;
}

template<bool>
web::json::value to_object(const std::map<std::string, primitive> &values) {
    using namespace web;
    json::value result = json::value::object();
    for (auto &pair: values) {
        result[pair.first] = json::value::boolean(pair.second.template get<bool>());
    }
    return result;
}

web::json::value controller::to_json(const value_holder &holder) {

    using namespace web;

    json::value result = json::value::object();
    if (holder.holds<primitive>()) {
        const auto &v = holder.get<primitive>();
        if (v.holds<int>()) {
            result["type"] = json::value::string("int");
            result["value"] = json::value::number(v.get<int>());
        } else if (v.holds<float>()) {
            result["type"] = json::value::string("float");
            result["value"] = json::value::number(v.get<float>());
        }
    } else if (holder.holds<vector>()) {
        const auto &v = holder.get<vector>();
        const auto &values = v.get_values();
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
    } else if (holder.holds<vector_ref>()) {
        return to_json(holder.get<vector_ref>().get(0));
    }

    return result;
}

std::string controller::to_string(const value_holder &holder) {

    using namespace web;
    json::value result = to_json(holder);
    std::stringstream stream;
    result.serialize(stream);

    return stream.str();
}

std::string controller::from_base64(const std::string &base64) {

    auto buffer = utility::conversions::from_base64(base64);

    std::ostringstream oss;
    std::copy(buffer.begin(), buffer.end(),
              std::ostream_iterator<unsigned char>(oss));

    return oss.str();
}