//
// Created by rainm on 2021/1/3.
//

#ifndef HUSKY_ENGINE_FUNCTION_H
#define HUSKY_ENGINE_FUNCTION_H

#include <vector>
#include "runtime/value_base.h"
#include "runtime/runtime.h"

#include "util/timer.h"

namespace husky {
    class func {
    public:
        static value_holder rank(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder avail(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder avg_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder sum_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder max_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder min_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder std_t(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder avg(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder sum(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder max(const runtime &rt, const std::vector<value_holder> &args);

        static value_holder min(const runtime &rt, const std::vector<value_holder> &args);

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

        template<typename OpType>
        static value_holder reduce_t(const runtime &rt, const std::vector<value_holder> &args, OpType op) {
            if (args.size() != 3) {
                throw std::runtime_error("invalid arguments pass to reduce_t");
            }

            auto maybe_ref = args[0];
            if (!maybe_ref.holds<vector_ref>()) {
                throw std::runtime_error("invalid arguments pass to reduce_t");
            }

            const auto &ref = maybe_ref.get<vector_ref>();

            int begin = args[1].get<primitive>().get<int>();
            int end = args[2].get<primitive>().get<int>();

            std::vector<vector> frames;
            for (int i = begin; i <= end; i++) {
                auto el = ref.get(i);
                frames.emplace_back(el);
            }

            auto_timer tmr("reduce_t on " + std::to_string(end - begin + 1) + " frames");

            vector reduced_v;
            for (int i = 0; i < frames.size(); i++) {
                if (i == 0) {
                    reduced_v = frames[i];
                } else {
                    reduced_v = vector::binary_operator(reduced_v, frames[i], op);
                }
            }

            return value_holder(reduced_v);
        }

        static value_holder avail_(const runtime &rt, const value_holder &holder, const primitive &default_value);

        static std::function<std::optional<primitive>(const std::string &)> value_getter_of(const value_holder &holder);


    };
}

#endif //HUSKY_ENGINE_FUNCTION_H
