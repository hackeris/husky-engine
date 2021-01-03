#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "runtime/ValueBase.h"
#include "runtime/GraphVM.h"

#include "lang/GraphCompiler.h"

#include <mysqlx/xdevapi.h>
#include <dal/DataRepository.h>

using ::std::cout;
using ::std::endl;
using namespace ::mysqlx;

using namespace antlr4;
using namespace antlrcpp;

int testCompiler() {

    std::string exp = "rank(roe, avg_t(roe, -2, 0) > 20) < 10";
    std::string date = "2020-09-10";

    auto host = "192.168.10.102";
    auto port = 3306;
    auto user = "root";
    auto pass = "toor";
    auto database = "husky_v2";

    auto dal = std::make_shared<DataRepository>(
            host, port, user, pass, database);
    auto rt = std::make_shared<Runtime>(date, dal);

    GraphVM gvm(rt);
    try {
        auto graph = GraphCompiler::compile(exp);
        ValueHolder value = gvm.evaluate(graph);
        std::cout << value.hold<Vector>() << std::endl;
    } catch (const std::runtime_error &error) {
        std::cout << error.what() << std::endl;
    }

    return 0;
}

int main(int argc, const char *argv[]) {

    testCompiler();

    return 0;
}
