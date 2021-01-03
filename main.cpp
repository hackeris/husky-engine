#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "api/Controller.h"
#include "runtime/ValueBase.h"

#include "dal/DataRepository.h"
#include "api/Router.h"

using ::std::cout;
using ::std::endl;
using namespace ::mysqlx;

std::optional<int> parse_port(int argc, const char *argv[]) {

    if (argc >= 2) {
        return std::make_optional(
                std::strtol(argv[1], nullptr, 10));
    }
    return std::nullopt;
}

int startService(int argc, const char *argv[]) {

    std::optional<int> maybe_port = parse_port(argc, argv);
    int port = maybe_port.value_or(8081);
    auto entry = "http://localhost:" + std::to_string(port);
    std::cout << "Will listen at: " << entry << std::endl;

    auto host = "192.168.10.102";
    auto db_port = 3306;
    auto user = "root";
    auto pass = "toor";
    auto database = "husky_v2";
    auto client = std::make_shared<Client>(
            "root:toor@192.168.10.102/husky_v2", DbDoc("    { \"pooling\": {\n"
                                                       "        \"enabled\": true,\n"
                                                       "        \"maxSize\": 25,\n"
                                                       "        \"queueTimeout\": 1000,\n"
                                                       "        \"maxIdleTime\": 5000}\n"
                                                       "    }"));
    auto dal = std::make_shared<DataRepository>(client);

    Controller api(dal);

    http_listener listener(entry);
    router route;

    route.support("/api/compute", methods::GET, [&api](const auto &req) {
        api.compute(req);
    });
    listener.support(route);

    try {
        listener.open().wait();
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(10));
        }
    }
    catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

int main(int argc, const char *argv[]) {

    startService(argc, argv);

    return 0;
}
