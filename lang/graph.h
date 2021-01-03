//
// Created by rainm on 2021/1/1.
//

#ifndef HUSKY_ENGINE_GRAPH_H
#define HUSKY_ENGINE_GRAPH_H

#include <any>
#include <string>
#include <utility>
#include <variant>
#include <vector>

class node_base {
public:
    virtual ~node_base() = default;
};

class literal : public node_base {
public:

    enum literal_type {
        int_value,
        float_value
    };

public:
    explicit literal(int value) : type(literal_type::int_value), value(value) {}

    explicit literal(float value) : type(literal_type::float_value), value(value) {}

    [[nodiscard]]
    bool is(const literal_type &t) const { return this->type == t; }

    template<typename ValueType>
    [[nodiscard]]
    ValueType get() const {
        return std::get<ValueType>(value);
    }

private:
    literal_type type;
    std::variant<int, float> value;
};

class identifier_ref : public node_base {
public:
    explicit identifier_ref(std::string &&name) : name(name) {}

    [[nodiscard]]
    const std::string &get_name() const {
        return name;
    }

private:
    std::string name;
};

class atom;

class expression;

using atom_ptr = std::shared_ptr<atom>;

using expression_ptr = std::shared_ptr<expression>;

class binary_op : public node_base {
public:
    enum op_type {
        op_add,
        op_sub,
        op_multi,
        op_div,
        op_and,
        op_or,
        op_equal,
        op_not_equal,
        op_greater,
        op_lower,
        op_greater_or_equal,
        op_lower_or_equal,
        op_power
    };
public:
    binary_op(op_type op, expression_ptr left, expression_ptr right)
            : op(op), left(std::move(left)), right(std::move(right)) {}

public:
    op_type op;
    expression_ptr left;
    expression_ptr right;
};

using unary_operand = std::variant<binary_op, atom_ptr>;

class unary_op : public node_base {
public:
    enum op_type {
        op_minus,
        op_not
    };
public:
    template<typename operand_type>
    unary_op(op_type op, operand_type operand) : op(op), operand(std::move(operand)) {}

public:
    op_type op;
    unary_operand operand;
};

using arg_list = std::shared_ptr<std::vector<expression_ptr>>;

class function_call : public node_base {
public:
    explicit function_call(std::string &&name, arg_list argList)
            : func(std::forward<std::string>(name)), args(std::move(argList)) {}

public:
    identifier_ref func;
    arg_list args;
};

class array_index : public node_base {
public:
    explicit array_index(identifier_ref ident, expression_ptr idx)
            : identifier(std::move(ident)), index(std::move(idx)) {}

public:
    identifier_ref identifier;
    expression_ptr index;
};

class atom : public node_base {
private:
    using child_type = std::variant<
            literal,
            identifier_ref,
            function_call,
            expression_ptr,
            array_index
    >;
    child_type child;
public:

    template<typename T>
    inline bool is() const {
        return std::holds_alternative<T>(child);
    }

    template<typename T>
    inline const T &get() const {
        return std::get<T>(child);
    }

    template<typename C>
    explicit atom(C child_):child(child_) {}
};

class expression : public node_base {
private:
    using child_type = std::variant<
            binary_op,
            unary_op,
            atom_ptr
    >;
    child_type child;
public:

    template<typename T>
    inline bool is() const {
        return std::holds_alternative<T>(child);
    }

    template<typename T>
    inline const T &get() const {
        return std::get<T>(child);
    }

    template<typename C>
    explicit expression(C child_):child(child_) {}
};

#endif //HUSKY_ENGINE_GRAPH_H
