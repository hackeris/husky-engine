//
// Created by rainm on 2021/1/3.
//

#include "router.h"

bool router::handle(const http_request &req) {

    try {
        return try_handle(req);
    } catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
        throw e;
    }
}

bool router::try_handle(const http_request &req) {

    auto &method = req.method();
    auto path = uri::decode(req.relative_uri().path());

    auto p_entry = handlers.find(path);
    if (p_entry != handlers.end()) {
        auto &entry = p_entry->second;
        auto p_method = entry.method_handlers.find(method);
        if (p_method != entry.method_handlers.end()) {
            auto &method_handler = p_method->second;
            method_handler(req);
            return true;
        }
        if (entry.default_handler.has_value()) {
            entry.default_handler.value()(req);
            return true;
        }
    }

    return false;
}
