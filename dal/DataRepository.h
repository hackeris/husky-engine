//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_COMPUTE_DATAREPOSITORY_H
#define HUSKY_COMPUTE_DATAREPOSITORY_H

#include <string>
#include <vector>

#include <mysqlx/xdevapi.h>

using ::mysqlx::Session;
using ::mysqlx::Schema;
using ::mysqlx::Table;
using ::mysqlx::RowResult;
using ::mysqlx::Row;
using ::mysqlx::Value;
using ::mysqlx::bytes;
using ::mysqlx::SqlResult;
using ::mysqlx::Client;

enum FactorType {
    Market,
    Financial,
    Formula
};

struct Factor {
    int id;
    std::string code;
    FactorType type;
    std::string formula;

public:
    static inline FactorType typeOf(int typeCode) {
        switch (typeCode) {
            case 0:
                return FactorType::Market;
            case 1:
                return FactorType::Financial;
            case 2:
                return FactorType::Formula;
            default:
                return FactorType::Market;
        }
    }
};

class DataRepository {
public:
    DataRepository(std::shared_ptr<Client> client);

    bool factorExists(const std::string &code);

    std::map<std::string, float> getFactorValues(
            const std::string &code, const std::string &date, int offset);

    std::vector<std::string> getSymbols(const std::string &date);

private:

    std::vector<std::string> getDates(Session &sess);

    std::vector<std::string> getSymbols(Session &sess, const std::string &date);

    Factor getFactor(Session& sess, const std::string &code);

    std::map<std::string, float> makeValues(const std::list<Row> &rows);

    std::map<std::string, float> getMarketValues(
            Session& sess, int id, const std::string &date, int offset);

    std::map<std::string, float> getFinancialValues(
            Session& sess, int id, const std::string &date, int offset);

    std::map<std::string, float> getFormulaValues(
            Session &sess, const std::string &formula, const std::string &date, int offset);

    std::string getDate(Session &sess, const std::string &base, int offset);

private:
    std::shared_ptr<Client> client;
};


#endif //HUSKY_COMPUTE_DATAREPOSITORY_H
