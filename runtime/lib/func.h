//
// Created by rainm on 2021/1/3.
//

#ifndef HUSKY_ENGINE_FUNCTION_H
#define HUSKY_ENGINE_FUNCTION_H

#include <vector>
#include "runtime/value_base.h"
#include "runtime/runtime.h"

namespace husky {
    class func {
    public:
        static value_holder rank(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder avail(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder avg_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder sum_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder std_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder avg(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder sum(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder std(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder zscore(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder noisy(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder log(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder sqrt(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder exp(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder drop_false(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder count(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder if_select(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder mask(const runtime &rt, const vector &v, const vector &mask_vec);

    private:
        static value_holder sqrt_(const value_holder &arg);

        static value_holder avail_(const runtime &rt, const value_holder& holder, const primitive& default_value);

        static std::function<std::optional<primitive>(const std::string &)> value_getter_of(const value_holder& holder);
    };
}

#endif //HUSKY_ENGINE_FUNCTION_H
