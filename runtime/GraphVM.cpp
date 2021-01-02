//
// Created by rainm on 2021/1/2.
//

#include "GraphVM.h"

#include <utility>

GraphVM::GraphVM(std::shared_ptr<Runtime> runtime)
        : runtime(std::move(runtime)) {
}

ValueHolder GraphVM::evaluate(const ExpressionPtr &exprPtr) {
    auto const &expr = *exprPtr.get();
    if (expr.is<BinaryOp>()) {
        return evaluate(expr.get<BinaryOp>());
    } else if (expr.is<UnaryOp>()) {
        return evaluate(expr.get<UnaryOp>());
    } else if (expr.is<AtomPtr>()) {
        return evaluate(expr.get<AtomPtr>());
    }
    throw std::runtime_error("unexpected expression child type");
}

ValueHolder GraphVM::evaluate(const BinaryOp &binaryOp) {
    auto left = evaluate(binaryOp.left);
    auto right = evaluate(binaryOp.right);
    switch (binaryOp.op) {
        case BinaryOp::Add:
            return left + right;
        case BinaryOp::Sub:
            return left - right;
        case BinaryOp::Multi:
            return left * right;
        case BinaryOp::Div:
            return left / right;
        case BinaryOp::And:
            return left && right;
        case BinaryOp::Or:
            return left || right;
        case BinaryOp::Equal:
            return left == right;
        case BinaryOp::NotEqual:
            return left != right;
        case BinaryOp::Greater:
            return left > right;
        case BinaryOp::Lower:
            return left < right;
        case BinaryOp::GreaterOrEqual:
            return left >= right;
        case BinaryOp::LowerOrEqual:
            return left <= right;
        case BinaryOp::Power:
            throw std::runtime_error("power is not implemented");
    }
}

ValueHolder GraphVM::evaluate(const UnaryOp &unaryOp) {
    auto operand = unaryOp.operand;
    switch (unaryOp.op) {
        case UnaryOp::Minus:
            return -evaluate(operand);
        case UnaryOp::Not:
            return !evaluate(operand);
    }
}

ValueHolder GraphVM::evaluate(const AtomPtr &atomPtr) {
    const Atom &atom = *atomPtr.get();
    if (atom.is<Literal>()) {
        return evaluate(atom.get<Literal>());
    } else if (atom.is<IdentifierRef>()) {
        return evaluate(atom.get<IdentifierRef>());
    } else if (atom.is<FunctionCall>()) {
        return evaluate(atom.get<FunctionCall>());
    } else if (atom.is<ExpressionPtr>()) {
        return evaluate(atom.get<ExpressionPtr>());
    } else if (atom.is<ArrayIndex>()) {
        return evaluate(atom.get<ArrayIndex>());
    }
    throw std::runtime_error("unsupported operation");
}

ValueHolder GraphVM::evaluate(const UnaryOperand &unaryOperand) {
    if (std::holds_alternative<BinaryOp>(unaryOperand)) {
        return evaluate(std::get<BinaryOp>(unaryOperand));
    } else if (std::holds_alternative<AtomPtr>(unaryOperand)) {
        return evaluate(std::get<AtomPtr>(unaryOperand));
    }
    throw std::runtime_error("unsupported operation");
}

ValueHolder GraphVM::evaluate(const Literal &literal) {
    if (literal.is(Literal::Type::Integer)) {
        return PrimitiveValue(literal.get<int>());
    } else if (literal.is(Literal::Type::Float)) {
        return PrimitiveValue(literal.get<float>());
    }
    throw std::runtime_error("unsupported operation");
}

ValueHolder GraphVM::evaluate(const IdentifierRef &identifier) {
    return runtime->evaluate(identifier);
}

ValueHolder GraphVM::evaluate(const FunctionCall &call) {

    std::vector<ValueHolder> args;
    std::transform(call.args->begin(), call.args->end(),
                   std::back_inserter(args),
                   [this](const ExpressionPtr &expr) -> ValueHolder {
                       return evaluate(expr);
                   });

    const std::string &functionName = call.func.getName();
    if (!runtime->hasFunction(functionName)) {
        throw std::runtime_error("cannot find function " + call.func.getName());
    }

    auto &f = runtime->getFunction(functionName);
    return f(args);
}

ValueHolder GraphVM::evaluate(const ArrayIndex &arrayIndex) {

    auto &identifier = arrayIndex.identifier;

    auto indexHolder = evaluate(arrayIndex.index);
    assert(indexHolder.hold<PrimitiveValue>());
    const auto &indexValue = indexHolder.get<PrimitiveValue>();
    assert(indexValue.valueIs<int>());

    int index = indexValue.get<int>();

    return runtime->evaluate(identifier, index);
}
