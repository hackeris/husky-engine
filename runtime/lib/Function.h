//
// Created by rainm on 2021/1/3.
//

#ifndef HUSKY_COMPUTE_FUNCTION_H
#define HUSKY_COMPUTE_FUNCTION_H

#include <vector>
#include "runtime/ValueBase.h"
#include "runtime/Runtime.h"

ValueHolder rank(const Runtime &runtime, const std::vector<ValueHolder> &args);

ValueHolder avail(const Runtime &runtime, const std::vector<ValueHolder> &args);

ValueHolder avgT(const Runtime &runtime, const std::vector<ValueHolder> &args);

ValueHolder dropFalse(const Runtime &runtime, const std::vector<ValueHolder> &args);

#endif //HUSKY_COMPUTE_FUNCTION_H
