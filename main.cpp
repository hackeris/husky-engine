#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <csignal>

#include "dal/data_repository.h"

#include "api/router.h"
#include "api/controller.h"

using namespace ::mysqlx;
using namespace husky;

std::function<void(void)> signal_handler;

void sig_int_handler(int) {
    std::cout << "on SIGINT" << std::endl;
    signal_handler();
}

/**
 *
  "client": {
     "pooling": {
        "enabled": true,
        "maxSize": 25,
        "queueTimeout": 1000,
        "maxIdleTime": 5000
      }
    }
 *
 */
int startService(int argc, const char *argv[]) {

    using husky::web::router;
    using namespace husky::api;

    std::string config_file = "config.json";
    if (argc > 1) {
        config_file = argv[1];
    }

    std::ifstream in(config_file);
    std::string config_json((std::istreambuf_iterator<char>(in)),
                            std::istreambuf_iterator<char>());

    std::istringstream iss(config_json);
    json::value config = json::value::parse(iss);

    auto host = config["host"].as_string();
    auto db_port = config["port"].as_integer();
    auto user = config["user"].as_string();
    auto pass = config["password"].as_string();
    auto database = config["database"].as_string();
    auto entry = config["entry"].as_string();
    auto client_config = config["client"].serialize();
    auto financial_batch_size = config["financial_batch_size"].as_integer();

    auto cache_size = config["cache_size"].as_integer();

    std::cout << "Will listen at: " << entry << std::endl;
    std::cout << "Use database from " << host << ":" << db_port << ", database: " << database << std::endl;

    std::string uri = user + ":" + pass + "@" + host + ":"
                      + std::to_string(db_port * 10) + "/" + database;
    auto client = std::make_shared<Client>(
            uri, DbDoc(client_config));

    auto cache = std::make_shared<value_cache>(cache_size);
    auto dal = std::make_shared<data_repository>(client, cache, financial_batch_size);

    controller api(dal, cache);
    router route;
    route.support("/api/compute", methods::POST,
                  [&api](const http_request &req) { api.compute_post(req); });
    route.support("/api/check", methods::POST,
                  [&api](const http_request &req) { api.syntax_check(req); });
    route.support("/api/cache", methods::GET,
                  [&api](const http_request &req) { api.cache_usage(req); });

    http_listener listener(entry);
    listener.support(route);

    volatile bool running = true;
    signal_handler = [&listener, &running] {
        std::cout << "exiting..." << std::endl;
        listener.close().wait();
        running = false;
    };
    signal(SIGINT, sig_int_handler);

    try {
        listener.open().wait();
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

int main(int argc, const char *argv[]) {

    startService(argc, argv);

    return 0;
}
