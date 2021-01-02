//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_COMPUTE_GRAPHVM_H
#define HUSKY_COMPUTE_GRAPHVM_H

#include <map>
#include <string>
#include <functional>

#include "lang/Graph.h"
#include "runtime/ValueBase.h"
#include "runtime/Runtime.h"

class GraphVM {
public:

    explicit GraphVM(std::shared_ptr<Runtime> runtime);

    ValueHolder evaluate(const ExpressionPtr &exprPtr);

    ValueHolder evaluate(const BinaryOp &binaryOp);

    ValueHolder evaluate(const UnaryOp &unaryOp);

    ValueHolder evaluate(const AtomPtr &atomPtr);

    ValueHolder evaluate(const UnaryOperand &unaryOperand);

    ValueHolder evaluate(const Literal &literal);

    ValueHolder evaluate(const IdentifierRef &identifier);

    ValueHolder evaluate(const FunctionCall &call);

    ValueHolder evaluate(const ArrayIndex &arrayIndex);

private:
    std::shared_ptr<Runtime> runtime;
};


#endif //HUSKY_COMPUTE_GRAPHVM_H
