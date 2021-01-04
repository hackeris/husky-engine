//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_ENGINE_GRAPHVM_H
#define HUSKY_ENGINE_GRAPHVM_H

#include <map>
#include <string>
#include <memory>
#include <functional>

#include "lang/graph.h"
#include "runtime/value_base.h"
#include "runtime/runtime.h"

namespace husky {

    class graph_vm {
    public:

        explicit graph_vm(std::shared_ptr<runtime> rt);

        value_holder evaluate(const expression_ptr &expr_ptr);

        value_holder evaluate(const binary_op &bop);

        value_holder evaluate(const unary_op &uop);

        value_holder evaluate(const atom_ptr &p_atom);

        value_holder evaluate(const unary_operand &unaryOperand);

        value_holder evaluate(const literal &literal);

        value_holder evaluate(const identifier_ref &identifier);

        value_holder evaluate(const function_call &call);

        value_holder evaluate(const array_index &expr);

    private:
        std::shared_ptr<runtime> p_rt;
    };

}

#endif //HUSKY_ENGINE_GRAPHVM_H
