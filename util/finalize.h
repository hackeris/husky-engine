//
// Created by rainm on 2021/1/7.
//

#ifndef HUSKY_ENGINE_FINALIZE_H
#define HUSKY_ENGINE_FINALIZE_H

#include <functional>
#include <utility>

class finalize {
public:
    inline explicit finalize(std::function<void(void)> dtor) : dtor(std::move(dtor)) {}

    inline ~finalize() { dtor(); }

private:
    std::function<void(void)> dtor;
};

#endif //HUSKY_ENGINE_FINALIZE_H
