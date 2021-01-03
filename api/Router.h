//
// Created by rainm on 2021/1/3.
//

#ifndef HUSKY_ENGINE_ROUTER_H
#define HUSKY_ENGINE_ROUTER_H

#include <map>
#include <optional>
#include <cpprest/http_listener.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace concurrency;

class router {

    using handler = std::function<void(const http_request &)>;

public:
    inline void operator()(const http_request &req) {
        if (!handle(req)) {
            req.reply(status_codes::NotFound);
        }
    }

    inline void support(const std::string &path, const handler &handler) {
        handlers[path].default_handler = handler;
    }

    inline void support(const std::string &path,
                 const method &method, const handler &handler) {
        handlers[path].method_handlers[method] = handler;
    }

private:

    bool handle(const http_request &req);

    bool try_handle(const http_request &req);

private:

    struct entry {
        std::optional<handler> default_handler;
        std::map<method, handler> method_handlers;
    };

    std::map<std::string, entry> handlers;
};

#endif //HUSKY_ENGINE_ROUTER_H
