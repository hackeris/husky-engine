//
// Created by rainm on 2021/1/2.
//

#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include "util/timer.h"
#include "data_repository.h"

#include "lang/graph_compiler.h"
#include "runtime/runtime.h"
#include "runtime/graph_vm.h"

using namespace husky;

data_repository::data_repository(std::shared_ptr<Client> client, std::shared_ptr<value_cache> cache)
        : client(std::move(client)), cache_(std::move(cache)) {
}

std::vector<std::string> data_repository::get_dates(Session &sess) {

    Schema schema = sess.getDefaultSchema();

    Table table = schema.getTable("trading_date");

    RowResult result = table.select("date_format(date, '%Y-%m-%d')")
            .where("status = 0")
            .orderBy("date")
            .execute();
    std::list<Row> rows = result.fetchAll();

    std::vector<std::string> dates;
    for (auto &row : rows) {
        Value &value = row[0];
        dates.push_back(value.get<std::string>());
    }
    return dates;
}

std::map<std::string, float> data_repository::get_factor_values(
        const std::string &code, const std::string &date, int offset) {

    auto_timer tmr("get_factor_values, code: " + code + ", date: "
                   + date + ", offset: " + std::to_string(offset));

    Session sess = client->getSession();

    auto factor_ = get_factor(sess, code);
    if (factor_.id <= 0) {
        sess.close();
        return std::map<std::string, float>();
    }

    std::optional<std::map<std::string, float>> values;
    if (factor_.type == factor_type::market) {
        values = get_market_values(sess, factor_, date, offset);
    } else if (factor_.type == factor_type::financial) {
        values = get_financial_values(sess, factor_, date, offset);
    } else if (factor_.type == factor_type::formula) {
        values = get_formula_values(sess, factor_, date, offset);
    }

    sess.close();

    if (values.has_value()) {
        return values.value();
    }

    throw std::runtime_error("unsupported factor_ type");
}

std::map<std::string, float>
data_repository::get_financial_values(Session &sess,  const factor& f, const std::string &date, int offset) {

    std::string sqlFormat = "("
                            "SELECT `symbol`,`value` FROM financial_factor_data "
                            " WHERE id = %d"
                            " AND symbol = '%s'"
                            " AND date <= '%s'"
                            " ORDER BY date DESC LIMIT %d, 1"
                            ")";

    const auto &symbols = get_symbols(sess, date);
    std::vector<std::string> raw_sqls;
    std::transform(symbols.begin(), symbols.end(),
                   std::back_inserter(raw_sqls),
                   [&date, offset, &f, sqlFormat](const std::string &symbol) -> std::string {
                       char buf[512];
                       snprintf(buf, 512, sqlFormat.c_str(), f.id, symbol.c_str(), date.c_str(), -offset);
                       return std::string(buf);
                   });

    auto join_sqls = [](std::vector<std::string>::iterator begin,
                        std::vector<std::string>::iterator end) -> auto {
        return std::accumulate(begin, end,
                               std::string(),
                               [](const std::string &acc, const std::string &el) -> std::string {
                                   return acc.empty() ? el : acc + " union " + el;
                               });
    };
    auto fetch_data = [&sess, this](const std::string &sql) -> auto {
        SqlResult result = sess.sql(sql)
                .execute();
        return make_values(result.fetchAll());
    };

    std::map<std::string, float> result;

    size_t chunk_size = 100;
    auto iter = raw_sqls.begin();
    while (iter != raw_sqls.end()) {
        auto diff = raw_sqls.end() - iter;
        auto end = iter + std::min((long) diff, (long) chunk_size);
        if (end != iter) {
            auto chunk = fetch_data(join_sqls(iter, end));
            result.insert(chunk.begin(), chunk.end());
        }
        iter = end;
    }

    return result;
}

std::vector<std::string> data_repository::get_symbols(const std::string &date) {

    Session sess = client->getSession();
    auto symbols = get_symbols(sess, date);
    sess.close();
    return symbols;
}

std::map<std::string, float> data_repository::make_values(const std::list<Row> &rows) {

    std::map<std::string, float> values;
    for (auto &row : rows) {
        auto &symbol = row[0];
        auto &value = row[1];
        if (value.isNull()) {
            continue;
        }
        values.emplace(symbol.get<std::string>(), value.get<double>());
    }
    return values;
}

bool data_repository::factor_exists(const std::string &code) {
    Session sess = client->getSession();
    auto factor_ = get_factor(sess, code);
    sess.close();
    return factor_.id > 0;
}

factor data_repository::get_factor(Session &sess, const std::string &code) {

    Schema schema = sess.getDefaultSchema();
    Table table = schema.getTable("factor");
    RowResult result = table.select("id", "code", "formula", "sourceType")
            .where("code = :code")
            .bind("code", code)
            .execute();
    Row row = result.fetchOne();
    if (row.isNull()) {
        return factor{0};
    }

    int id = row[0].get<int>();
    std::string formula;
    auto formula_col = row[2];
    if (!formula_col.isNull()) {
        formula = formula_col.get<std::string>();
    }
    int typeCode = row[3].get<int>();
    factor_type type = factor::type_of(typeCode);

    return factor{id, code, type, formula};
}

std::map<std::string, float> data_repository::get_market_values(
        Session &sess,  const factor& f, const std::string &date, int offset) {

    const std::string &date_ = get_date(sess, date, offset);
    if (date_.empty()) {
        return std::map<std::string, float>();
    }

    if (cache_->size() > 0) {
        auto values = cache_->get_values(f.code, date_);
        if (values.has_value()) {
            return values.value();
        }
    }

    Schema schema = sess.getDefaultSchema();
    Table table = schema.getTable("factor_data");
    RowResult result = table.select("symbol", "value")
            .where("id = :id and date = :date")
            .bind("id", std::to_string(f.id))
            .bind("date", date_)
            .execute();
    auto values = make_values(result.fetchAll());

    if (cache_->size() > 0) {
        cache_->put(f.code, date_, values);
    }

    return values;
}

std::map<std::string, float>
data_repository::get_formula_values(
        Session &sess,  const factor& f, const std::string &date, int offset) {

    const std::string &date_ = get_date(sess, date, offset);
    if (date_.empty()) {
        return std::map<std::string, float>();
    }

    if (cache_->size() > 0) {
        auto values = cache_->get_values(f.formula, date_);
        if (values.has_value()) {
            return values.value();
        }
    }

    auto graph = graph_compiler::compile(f.formula);
    auto rt = std::make_shared<runtime>(
            date_, std::make_shared<data_repository>(*this));
    graph_vm vm(rt);

    value_holder value = vm.run(graph);

    vector vec = value.get<vector>();
    const std::set<std::string> &keys = vec.keys();
    std::map<std::string, float> values;
    std::transform(keys.begin(), keys.end(),
                   std::inserter(values, values.end()),
                   [&vec](const std::string &key) -> std::pair<std::string, float> {
                       auto el = vec.get(key);
                       return std::make_pair(key, el.value().get<float>());
                   });

    if (cache_->size() > 0) {
        cache_->put(f.formula, date_, values);
    }

    return values;
}

std::string data_repository::get_date(Session &sess, const std::string &base, int offset) {

    const std::vector<std::string> &dates = get_dates(sess);
    auto pos = std::find(dates.begin(), dates.end(), base) - dates.begin();
    auto exactPos = pos + offset;
    if (exactPos >= dates.size() || exactPos < 0) {
        return "";
    }
    return dates[pos + offset];
}

std::vector<std::string> data_repository::get_symbols(Session &sess, const std::string &date) {

    const auto &factor_ = get_factor(sess, "close_price_backward");
    const auto &values = get_market_values(sess, factor_, date, 0);

    std::vector<std::string> symbols;
    std::transform(values.begin(), values.end(),
                   std::back_inserter(symbols),
                   [](const auto &pair) -> std::string {
                       return pair.first;
                   });
    return symbols;
}
