//
// Created by rainm on 2021/1/3.
//

#ifndef HUSKY_ENGINE_FUNCTION_H
#define HUSKY_ENGINE_FUNCTION_H

#include <vector>
#include "runtime/value_base.h"
#include "runtime/runtime.h"

value_holder rank(const runtime &rt, const std::vector<value_holder> &args);

value_holder avail(const runtime &rt, const std::vector<value_holder> &args);

value_holder avg_t(const runtime &rt, const std::vector<value_holder> &args);

value_holder drop_false(const runtime &rt, const std::vector<value_holder> &args);

#endif //HUSKY_ENGINE_FUNCTION_H
