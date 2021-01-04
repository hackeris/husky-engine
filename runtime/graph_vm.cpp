//
// Created by rainm on 2021/1/2.
//

#include "value_base.h"
#include "graph_vm.h"

#include <utility>

using namespace husky;

graph_vm::graph_vm(std::shared_ptr<runtime> rt)
        : p_rt(std::move(rt)) {
}

value_holder graph_vm::evaluate(const expression_ptr &expr_ptr) {
    auto const &expr = *expr_ptr.get();
    if (expr.is<binary_op>()) {
        return evaluate(expr.get<binary_op>());
    } else if (expr.is<unary_op>()) {
        return evaluate(expr.get<unary_op>());
    } else if (expr.is<atom_ptr>()) {
        return evaluate(expr.get<atom_ptr>());
    }
    throw std::runtime_error("unexpected expression child type");
}

value_holder graph_vm::evaluate(const binary_op &bop) {
    auto left = evaluate(bop.left);
    auto right = evaluate(bop.right);
    switch (bop.op) {
        case binary_op::op_add:
            return left + right;
        case binary_op::op_sub:
            return left - right;
        case binary_op::op_multi:
            return left * right;
        case binary_op::op_div:
            return left / right;
        case binary_op::op_and:
            return left && right;
        case binary_op::op_or:
            return left || right;
        case binary_op::op_equal:
            return left == right;
        case binary_op::op_not_equal:
            return left != right;
        case binary_op::op_greater:
            return left > right;
        case binary_op::op_lower:
            return left < right;
        case binary_op::op_greater_or_equal:
            return left >= right;
        case binary_op::op_lower_or_equal:
            return left <= right;
        case binary_op::op_power:
            throw std::runtime_error("power is not implemented");
    }
}

value_holder graph_vm::evaluate(const unary_op &uop) {
    auto operand = uop.operand;
    switch (uop.op) {
        case unary_op::op_minus:
            return -evaluate(operand);
        case unary_op::op_not:
            return !evaluate(operand);
    }
}

value_holder graph_vm::evaluate(const atom_ptr &p_atom) {
    const atom &atom_ = *p_atom.get();
    if (atom_.is<literal>()) {
        return evaluate(atom_.get<literal>());
    } else if (atom_.is<identifier_ref>()) {
        return evaluate(atom_.get<identifier_ref>());
    } else if (atom_.is<function_call>()) {
        return evaluate(atom_.get<function_call>());
    } else if (atom_.is<expression_ptr>()) {
        return evaluate(atom_.get<expression_ptr>());
    } else if (atom_.is<array_index>()) {
        return evaluate(atom_.get<array_index>());
    }
    throw std::runtime_error("unsupported operation");
}

value_holder graph_vm::evaluate(const unary_operand &unaryOperand) {
    if (std::holds_alternative<binary_op>(unaryOperand)) {
        return evaluate(std::get<binary_op>(unaryOperand));
    } else if (std::holds_alternative<atom_ptr>(unaryOperand)) {
        return evaluate(std::get<atom_ptr>(unaryOperand));
    }
    throw std::runtime_error("unsupported operation");
}

value_holder graph_vm::evaluate(const literal &literal) {
    if (literal.is(literal::literal_type::int_value)) {
        return primitive(literal.get<int>());
    } else if (literal.is(literal::literal_type::float_value)) {
        return primitive(literal.get<float>());
    }
    throw std::runtime_error("unsupported operation");
}

value_holder graph_vm::evaluate(const identifier_ref &identifier) {
    return p_rt->evaluate(identifier);
}

value_holder graph_vm::evaluate(const function_call &call) {

    std::vector<value_holder> args;
    std::transform(call.args->begin(), call.args->end(),
                   std::back_inserter(args),
                   [this](const expression_ptr &expr) -> value_holder {
                       return evaluate(expr);
                   });

    const std::string &name = call.func.get_name();
    if (!p_rt->has_function(name)) {
        throw std::runtime_error("cannot find function " + call.func.get_name());
    }

    auto &f = p_rt->get_function(name);
    return f(*p_rt, args);
}

value_holder graph_vm::evaluate(const array_index &expr) {

    const identifier_ref &identifier = expr.identifier;

    value_holder holder = evaluate(expr.index);
    assert(holder.holds<primitive>());
    auto &value = holder.get<primitive>();
    assert(value.holds<int>());

    int index = value.get<int>();

    return p_rt->evaluate(identifier, index);
}
