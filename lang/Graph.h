//
// Created by rainm on 2021/1/1.
//

#ifndef HUSKY_COMPUTE_GRAPH_H
#define HUSKY_COMPUTE_GRAPH_H

#include <any>
#include <string>
#include <utility>
#include <variant>
#include <vector>

class Node {
public:
    virtual ~Node() = default;
};

class Literal : public Node {
public:

    enum LiteralType {
        Integer,
        Float
    };

    using Type = LiteralType;

public:
    explicit Literal(int value) : type(Type::Integer), value(value) {}

    explicit Literal(float value) : type(Type::Float), value(value) {}

    [[nodiscard]]
    bool is(const Type &t) const { return this->type == t; }

    template<typename ValueType>
    [[nodiscard]]
    ValueType get() const {
        return std::get<ValueType>(value);
    }

private:
    LiteralType type;
    std::variant<int, float> value;
};

class IdentifierRef : public Node {
public:
    explicit IdentifierRef(std::string &&name) : name(name) {}

    [[nodiscard]]
    const std::string &getName() const {
        return name;
    }

private:
    std::string name;
};

class Atom;

class Expression;

using AtomPtr = std::shared_ptr<Atom>;

using ExpressionPtr = std::shared_ptr<Expression>;

class BinaryOp : public Node {
public:
    enum Type {
        Add,
        Sub,
        Multi,
        Div,
        And,
        Or,
        Equal,
        NotEqual,
        Greater,
        Lower,
        GreaterOrEqual,
        LowerOrEqual,
        Power
    };
public:
    BinaryOp(Type op, ExpressionPtr left, ExpressionPtr right)
            : op(op), left(std::move(left)), right(std::move(right)) {}

public:
    Type op;
    ExpressionPtr left;
    ExpressionPtr right;
};

using UnaryOperand = std::variant<BinaryOp, AtomPtr>;

class UnaryOp : public Node {
public:
    enum Type {
        Minus,
        Not
    };
public:
    template<typename OperandType>
    UnaryOp(Type op, OperandType operand) : op(op), operand(std::move(operand)) {}

public:
    Type op;
    UnaryOperand operand;
};

using ArgList = std::shared_ptr<std::vector<ExpressionPtr>>;

class FunctionCall : public Node {
public:
    explicit FunctionCall(std::string &&name, ArgList argList)
            : func(std::forward<std::string>(name)), args(std::move(argList)) {}

public:
    IdentifierRef func;
    ArgList args;
};

class ArrayIndex : public Node {
public:
    explicit ArrayIndex(IdentifierRef ident, ExpressionPtr idx)
            : identifier(std::move(ident)), index(std::move(idx)) {}

public:
    IdentifierRef identifier;
    ExpressionPtr index;
};

class Atom : public Node {
private:
    using ChildType = std::variant<
            Literal,
            IdentifierRef,
            FunctionCall,
            ExpressionPtr,
            ArrayIndex
    >;
    ChildType child;
public:

    template<typename T>
    inline bool is() const {
        return std::holds_alternative<T>(child);
    }

    template<typename T>
    inline const T &get() const {
        return std::get<T>(child);
    }

    template<typename Child>
    explicit Atom(Child child_):child(child_) {}
};

class Expression : public Node {
private:
    using ChildType = std::variant<
            BinaryOp,
            UnaryOp,
            AtomPtr
    >;
    ChildType child;
public:

    template<typename T>
    inline bool is() const {
        return std::holds_alternative<T>(child);
    }

    template<typename T>
    inline const T &get() const {
        return std::get<T>(child);
    }

    template<typename Child>
    explicit Expression(Child child_):child(child_) {}
};

#endif //HUSKY_COMPUTE_GRAPH_H
