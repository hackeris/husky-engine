//
// Created by rainm on 2021/1/2.
//

#include <iostream>
#include <algorithm>
#include <numeric>
#include "DataRepository.h"

#include "lang/GraphCompiler.h"
#include "runtime/Runtime.h"
#include "runtime/GraphVM.h"

DataRepository::DataRepository(
        const std::string &host, int port, const std::string &user,
        const std::string &password, const std::string &database)
        //  should use port * 10
        : session(std::make_shared<Session>(host, port * 10, user, password, database)) {
    schema = std::make_shared<Schema>(
            session->getSchema(database, true));
}

std::vector<std::string> DataRepository::getDates() {

    Table table = schema->getTable("trading_date");

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

std::map<std::string, float> DataRepository::getFactorValues(
        const std::string &code, const std::string &date, int offset) {

    auto factor = getFactor(code);
    if (factor.id <= 0) {
        return std::map<std::string, float>();
    }

    if (factor.type == FactorType::Market) {
        return getMarketValues(factor.id, date, offset);
    } else if (factor.type == FactorType::Financial) {
        return getFinancialValues(factor.id, date, offset);
    } else if (factor.type == FactorType::Formula) {
        return getFormulaValues(factor.formula, date, offset);
    }

    throw std::runtime_error("unsupported factor type");
}

std::map<std::string, float>
DataRepository::getFinancialValues(int id, const std::string &date, int offset) {

    std::string sqlFormat = "("
                            "SELECT `symbol`,`value` FROM financial_factor_data "
                            " WHERE id = %d"
                            " AND symbol = '%s'"
                            " AND date <= '%s'"
                            " ORDER BY date DESC LIMIT %d, 1"
                            ")";

    const auto &symbols = getSymbols(date);
    std::vector<std::string> rowSqls;
    std::transform(symbols.begin(), symbols.end(),
                   std::back_inserter(rowSqls),
                   [&date, offset, id, sqlFormat](const std::string &symbol) -> std::string {
                       char buf[512];
                       snprintf(buf, 512, sqlFormat.c_str(), id, symbol.c_str(), date.c_str(), -offset);
                       return std::string(buf);
                   });

    auto sql = std::accumulate(rowSqls.begin(), rowSqls.end(),
                               std::string(),
                               [](const std::string &acc, const std::string &el) -> std::string {
                                   return acc.empty() ? el : acc + " union " + el;
                               });

    SqlResult result = session->sql(sql)
            .execute();
    return makeValues(result.fetchAll());
}

std::vector<std::string> DataRepository::getSymbols(const std::string &date) {

    const auto &values = getFactorValues("close_price_backward", date, 0);

    std::vector<std::string> symbols;
    std::transform(values.begin(), values.end(),
                   std::back_inserter(symbols),
                   [](const auto &pair) -> std::string {
                       return pair.first;
                   });
    return symbols;
}

std::map<std::string, float> DataRepository::makeValues(const std::list<Row> &rows) {

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

bool DataRepository::factorExists(const std::string &code) {
    auto factor = getFactor(code);
    return factor.id > 0;
}

Factor DataRepository::getFactor(const std::string &code) {
    Table table = schema->getTable("factor");
    RowResult result = table.select("id", "code", "formula", "sourceType")
            .where("code = :code")
            .bind("code", code)
            .execute();
    Row row = result.fetchOne();
    if (row.isNull()) {
        return Factor{0};
    }

    int id = row[0].get<int>();
    std::string formula;
    auto formulaCol = row[2];
    if (!formulaCol.isNull()) {
        formula = formulaCol.get<std::string>();
    }
    int typeCode = row[3].get<int>();
    FactorType type = Factor::typeOf(typeCode);

    return Factor{id, code, type, formula};
}

std::map<std::string, float> DataRepository::getMarketValues(int id, const std::string &date, int offset) {

    const std::string &exactDate = getDate(date, offset);
    if (exactDate.empty()) {
        return std::map<std::string, float>();
    }

    Table table = schema->getTable("factor_data");
    RowResult result = table.select("symbol", "value")
            .where("id = :id and date = :date")
            .bind("id", std::to_string(id))
            .bind("date", exactDate)
            .execute();
    return makeValues(result.fetchAll());
}

std::map<std::string, float>
DataRepository::getFormulaValues(const std::string &formula, const std::string &date, int offset) {

    const std::string &exactDate = getDate(date, offset);
    if (exactDate.empty()) {
        return std::map<std::string, float>();
    }

    auto expression = GraphCompiler::compile(formula);
    auto runtime = std::make_shared<Runtime>(
            exactDate, std::make_shared<DataRepository>(*this));
    GraphVM vm(runtime);

    ValueHolder value = vm.evaluate(expression);
    if (!value.hold<Vector>()) {
        return std::map<std::string, float>();
    }

    Vector vec = value.get<Vector>();
    const std::set<std::string> &keys = vec.keys();
    std::map<std::string, float> values;
    std::transform(keys.begin(), keys.end(),
                   std::inserter(values, values.end()),
                   [&vec](const std::string &key) -> std::pair<std::string, float> {
                       auto el = vec.get(key);
                       return std::make_pair(key, el.value().get<float>());
                   });

    return values;
}

std::string DataRepository::getDate(const std::string &base, int offset) {
    const std::vector<std::string> &dates = getDates();
    auto pos = std::find(dates.begin(), dates.end(), base) - dates.begin();
    auto exactPos = pos + offset;
    if (exactPos >= dates.size() || exactPos < 0) {
        return "";
    }
    return dates[pos + offset];
}
