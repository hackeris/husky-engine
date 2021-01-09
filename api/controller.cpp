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

void controller::compute_post(const http_request &req) const {

    using concurrency::streams::stringstreambuf;

    stringstreambuf buffer;
    req.body().read_to_end(buffer).wait();
    std::string content = buffer.collection();

    json::value body = json::value::parse(content);

    auto date = body["date"].as_string();
    auto formula = body["formula"].as_string();

    auto_timer tmr("compute values of '" + formula + "' at " + date);

    std::vector<syntax_error_item> errors;
    graph_compiler::syntax_check(formula, errors);
    if (errors.empty()) {
        auto result = compute(formula, date);
        auto res = to_json(formula, date, result);
        req.reply(status_codes::OK, res);
    } else {
        json::value res = json::value::object();
        res["errors"] = to_json(errors);
        req.reply(status_codes::OK, res);
    }
}

void controller::syntax_check(const http_request &req) const {

    using namespace web;
    using concurrency::streams::stringstreambuf;

    stringstreambuf buffer;
    req.body().read_to_end(buffer).wait();
    std::string content = buffer.collection();

    json::value body = json::value::parse(content);

    auto formula = body["formula"].as_string();

    std::vector<syntax_error_item> errors;
    graph_compiler::syntax_check(formula, errors);

    json::value res = json::value::object();
    res["errors"] = to_json(errors);

    req.reply(status_codes::OK, res);
}

value_holder controller::compute(const std::string &formula, const std::string &date) const {

    cache_key key = cache_key{formula, date};

    std::optional<value_holder> cached
            = const_cast<controller *>(this)->cache_.get(key);
    if (cached.has_value()) {
        return cached.value();
    }

    auto rt = std::make_shared<runtime>(date, dal);
    auto graph = graph_compiler::compile(formula);

    graph_vm gvm(rt);

    value_holder value = gvm.run(graph);
    const_cast<controller *>(this)->cache_.put(key, value);
    return value;
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

web::json::value controller::to_json(const std::string &formula, const std::string &date, const value_holder &holder) {

    using namespace web;

    json::value result = json::value::object();
    result["date"] = json::value::string(date);
    result["formula"] = json::value::string(formula);
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
    }

    return result;
}

json::value controller::to_json(const std::vector<syntax_error_item> &errors) {

    if (!errors.empty()) {
        std::vector<json::value> error_values;
        std::transform(errors.begin(), errors.end(),
                       std::back_inserter(error_values),
                       [](const syntax_error_item &err) {
                           json::value val = json::value::object();
                           val["line"] = json::value::number((int) err.line);
                           val["pos"] = json::value::number((int) err.pos);
                           val["err"] = json::value::string(err.msg);
                           return val;
                       });
        return json::value::array(error_values);
    } else {
        return json::value::array();
    }
}
