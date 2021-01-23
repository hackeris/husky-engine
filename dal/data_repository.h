//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_ENGINE_DATAREPOSITORY_H
#define HUSKY_ENGINE_DATAREPOSITORY_H

#include <string>
#include <vector>

#include <mysqlx/xdevapi.h>

#include "dal/value_cache.h"

using ::mysqlx::Session;
using ::mysqlx::Schema;
using ::mysqlx::Table;
using ::mysqlx::RowResult;
using ::mysqlx::Row;
using ::mysqlx::Value;
using ::mysqlx::bytes;
using ::mysqlx::SqlResult;
using ::mysqlx::Client;

namespace husky {

    enum factor_type {
        market,
        financial,
        formula
    };

    struct factor {
        int id;
        std::string code;
        factor_type type;
        std::string formula;

    public:
        static inline factor_type type_of(int code) {
            switch (code) {
                case 0:
                    return factor_type::market;
                case 1:
                    return factor_type::financial;
                case 2:
                    return factor_type::formula;
                default:
                    return factor_type::market;
            }
        }
    };

    class data_repository {
    public:
        explicit data_repository(
                std::shared_ptr<Client> client,
                std::shared_ptr<value_cache> cache,
                size_t financial_batch_size);

        bool factor_exists(const std::string &code);

        std::map<std::string, float> get_factor_values(
                const std::string &code, const std::string &date, int offset);

        std::vector<std::string> get_symbols(const std::string &date);

    private:

        std::vector<std::string> get_dates(Session &sess);

        std::vector<std::string> get_symbols(Session &sess, const std::string &date);

        factor get_factor(Session &sess, const std::string &code);

        std::map<std::string, float> make_values(const std::list<Row> &rows);

        std::map<std::string, float> get_market_values(
                Session &sess, const factor &f, const std::string &date, int offset);

        std::map<std::string, float> get_financial_values(
                Session &sess, const factor &f, const std::string &date, int offset);

        std::map<std::string, float> get_formula_values(
                Session &sess, const factor &f, const std::string &date, int offset);

        std::string get_date(Session &sess, const std::string &base, int offset);

    private:
        size_t financial_batch_size_;
        std::shared_ptr<Client> client;
        std::shared_ptr<value_cache> cache_;
    };

}

#endif //HUSKY_ENGINE_DATAREPOSITORY_H
