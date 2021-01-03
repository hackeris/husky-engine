//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_COMPUTE_VALUEBASE_H
#define HUSKY_COMPUTE_VALUEBASE_H

#include <set>
#include <map>
#include <string>
#include <optional>
#include <utility>
#include <variant>

namespace ops {
    struct add {
    public:
        template<typename T>
        T operator()(const T &left, const T &right) {
            return left + right;
        }
    };

    struct sub {
    public:
        template<typename T>
        T operator()(const T &left, const T &right) {
            return left - right;
        }
    };

    struct multi {
    public:
        template<typename T>
        T operator()(const T &left, const T &right) {
            return left * right;
        }
    };

    struct div {
    public:
        template<typename T>
        T operator()(const T &left, const T &right) {
            return left / right;
        }
    };

    struct less {
    public:
        template<typename T>
        decltype(auto) operator()(const T &left, const T &right) {
            return left < right;
        }
    };

    struct greater {
    public:
        template<typename T>
        decltype(auto) operator()(const T &left, const T &right) {
            return left > right;
        }
    };

    struct less_or_equal {
    public:
        template<typename T>
        decltype(auto) operator()(const T &left, const T &right) {
            return left <= right;
        }
    };

    struct greater_or_equal {
    public:
        template<typename T>
        decltype(auto) operator()(const T &left, const T &right) {
            return left > right;
        }
    };

    struct not_equal {
    public:
        template<typename T>
        decltype(auto) operator()(const T &left, const T &right) {
            return left != right;
        }
    };

    struct equal {
    public:
        template<typename T>
        decltype(auto) operator()(const T &left, const T &right) {
            return left == right;
        }
    };

    struct logical_not {
    public:
        template<typename T>
        decltype(auto) operator()(const T &value) {
            return !value;
        }
    };

    struct minus {
    public:
        template<typename T>
        decltype(auto) operator()(const T &value) {
            return -value;
        }
    };
}

class ValueBase {
public:
    template<typename Derived>
    [[nodiscard]] inline bool is() const {
        auto *ptr = dynamic_cast<const Derived *>(this);
        return ptr != nullptr;
    }

    template<typename Derived>
    [[nodiscard]] inline const Derived &as() const {
        auto *ptr = dynamic_cast<const Derived *>(this);
        assert(ptr != nullptr);
        return *ptr;
    }

    ValueBase() = default;

    virtual ~ValueBase() = default;
};

class PrimitiveValue : public ValueBase {
public:
    template<typename ValueType>
    PrimitiveValue(ValueType value):value(value) {} // NOLINT(google-explicit-constructor)

    PrimitiveValue(const PrimitiveValue &) = default;

    friend inline PrimitiveValue operator+(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::add());
    }

    friend inline PrimitiveValue operator-(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::sub());
    }

    friend inline PrimitiveValue operator*(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::multi());
    }

    friend inline PrimitiveValue operator/(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::div());
    }

    friend inline PrimitiveValue operator>(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::greater());
    }

    friend inline PrimitiveValue operator<(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::less());
    }

    friend inline PrimitiveValue operator>=(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::greater_or_equal());
    }

    friend inline PrimitiveValue operator<=(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::less_or_equal());
    }

    friend inline PrimitiveValue operator!=(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::not_equal());
    }

    friend inline PrimitiveValue operator==(const PrimitiveValue &left, const PrimitiveValue &right) {
        return binaryOperator<>(left, right, ops::equal());
    }

    friend inline PrimitiveValue operator&&(const PrimitiveValue &left, const PrimitiveValue &right) {
        if (left.holds<bool>() && right.holds<bool>()) {
            return PrimitiveValue(left.get<bool>() && right.get<bool>());
        }
        throw std::runtime_error("unexpected type on operator");
    }

    friend inline PrimitiveValue operator||(const PrimitiveValue &left, const PrimitiveValue &right) {
        if (left.holds<bool>() && right.holds<bool>()) {
            return PrimitiveValue(left.get<bool>() || right.get<bool>());
        }
        throw std::runtime_error("unexpected type on operator");
    }

    friend inline PrimitiveValue operator-(const PrimitiveValue &operand) {
        return unaryOperator(operand, ops::minus());
    }

    friend inline PrimitiveValue operator!(const PrimitiveValue &operand) {
        return unaryOperator(operand, ops::logical_not());
    }

    friend inline PrimitiveValue power(const PrimitiveValue &left, const PrimitiveValue &right) {
        if (left.holds<int>() && right.holds<int>()) {
            return PrimitiveValue((int) round(pow(left.get<int>(), right.get<int>())));
        } else if (left.holds<float>() || right.holds<float>()) {
            auto leftVal = left.holds<float>() ? left.get<float>() : (float) left.get<int>();
            auto rightVal = right.holds<float>() ? right.get<float>() : (float) right.get<int>();
            return PrimitiveValue(pow(leftVal, rightVal));
        }
        throw std::runtime_error("unexpected type on operator");
    }

    template<typename ValueType>
    [[nodiscard]] inline bool holds() const {
        return std::holds_alternative<ValueType>(value);
    }

    template<typename ValueType>
    [[nodiscard]] inline ValueType get() const {
        return std::get<ValueType>(value);
    }

private:

    template<class OpType>
    inline static PrimitiveValue binaryOperator(
            const PrimitiveValue &left, const PrimitiveValue &right, OpType op) {

        if (left.holds<int>() && right.holds<int>()) {
            return op(left.get<int>(), right.get<int>());
        } else if (left.holds<float>() && right.holds<float>()) {
            return op(left.get<float>(), right.get<float>());
        } else if (left.holds<float>() && right.holds<int>()) {
            return op(left.get<float>(), (float) right.get<int>());
        } else if (left.holds<int>() && right.holds<float>()) {
            return op((float) left.get<int>(), right.get<float>());
        }
        throw std::runtime_error("unexpected type on operator");
    }

    template<class OpType>
    inline static PrimitiveValue unaryOperator(const PrimitiveValue &value, OpType op) {
        if (value.holds<int>()) {
            return op(value.get<int>());
        } else if (value.holds<float>()) {
            return op(value.get<float>());
        } else if (value.holds<bool>()) {
            return op(value.get<bool>());
        }
        throw std::runtime_error("unexpected type on operator");
    }

private:
    std::variant<int, float, bool> value;
};

class Vector : public ValueBase {
public:
    Vector() : values(std::make_shared<std::map<std::string, PrimitiveValue>>()) {}

    Vector(std::map<std::string, PrimitiveValue> &&values)
            : values(std::make_shared<std::map<std::string, PrimitiveValue>>(values)) {}

    friend Vector operator+(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::add());
    }

    friend Vector operator-(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::sub());
    }

    friend Vector operator*(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::multi());
    }

    friend Vector operator/(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::div());
    }

    friend Vector operator>(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::greater());
    }

    friend Vector operator<(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::less());
    }

    friend Vector operator>=(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::greater_or_equal());
    }

    friend Vector operator<=(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::less_or_equal());
    }

    friend Vector operator!=(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::not_equal());
    }

    friend Vector operator==(const Vector &left, const Vector &right) {
        return binaryOperator(left, right, ops::equal());
    }

    friend Vector operator||(const Vector &left, const Vector &right) {
        return binaryOperator(left, right,
                              [](auto &left, auto &right) -> decltype(auto) { return left || right; });
    }

    friend Vector operator&&(const Vector &left, const Vector &right) {
        return binaryOperator(left, right,
                              [](auto &left, auto &right) -> decltype(auto) { return left && right; });
    }

    friend Vector operator-(const Vector &operand) {
        return unaryOperator(operand, ops::minus());
    }

    friend Vector operator!(const Vector &operand) {
        return unaryOperator(operand, ops::logical_not());
    }

    template<class OpType>
    inline static Vector binaryOperator(const Vector &left, const Vector &right, OpType op) {

        std::set<std::string> leftKeys = left.keys()
        , rightKeys = right.keys();

        std::set<std::string> allKeys;
        std::set_union(leftKeys.begin(), leftKeys.end(),
                       rightKeys.begin(), rightKeys.end(),
                       std::inserter(allKeys, allKeys.begin()));

        Vector result;
        auto &resultMap = result.values;
        for (auto &it: allKeys) {
            if (left.contains(it) && right.contains(it)) {
                auto leftVal = left.get(it);
                auto rightVal = right.get(it);
                resultMap->emplace(it, op(leftVal.value(), rightVal.value()));
            }
        }
        return result;
    }

    template<class OpType>
    inline static Vector unaryOperator(const Vector &operand, OpType op) {

        std::set<std::string> allKeys = operand.keys();

        Vector result;
        auto &resultMap = result.values;
        for (auto &it: allKeys) {
            auto operandValue = operand.get(it);
            resultMap->emplace(it, op(operandValue.value()));
        }
        return result;
    }

    [[nodiscard]]
    std::set<std::string> keys() const {
        std::set<std::string> keys;
        std::transform(values->begin(), values->end(),
                       std::inserter(keys, keys.begin()),
                       [](const auto &pair) -> std::string { return pair.first; });
        return keys;
    }

    [[nodiscard]]
    inline bool contains(const std::string &label) const {
        return values->find(label) != values->end();
    }

    inline void put(const std::string &label, const PrimitiveValue &value) {
        values->emplace(label, value);
    }

    [[nodiscard]]
    const std::map<std::string, PrimitiveValue> &getValues() const {
        return *values;
    }

    [[nodiscard]]
    inline std::optional<PrimitiveValue> get(const std::string &label) const {
        auto iter = values->find(label);
        if (iter != values->end()) {
            return std::optional<PrimitiveValue>((*iter).second);
        }
        return std::nullopt;
    }

    friend class ValueHolder;

private:
    std::shared_ptr<std::map<std::string, PrimitiveValue>> values;
};

class VectorRef : public ValueBase {
public:
    VectorRef(std::function<Vector(int)> getter) : getter(std::move(getter)) {}

    inline Vector get(int index) const {
        return getter(index);
    }

private:
    std::function<Vector(int)> getter;
};

class ValueHolder {
public:
    template<typename ValueType>
    ValueHolder(const ValueType &value)
            :valuePtr(std::make_shared<ValueType>(std::move(value))) {}

public:
    template<typename T>
    [[nodiscard]] inline bool holds() const {
        const T *ptr = dynamic_cast<const T *>(valuePtr.get());
        return ptr != nullptr;
    }

    template<typename T>
    [[nodiscard]] inline const T &get() const {
        return *std::dynamic_pointer_cast<T>(valuePtr);
    }

    friend ValueHolder operator+(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::add());
    }

    friend ValueHolder operator-(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::sub());
    }

    friend ValueHolder operator*(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::multi());
    }

    friend ValueHolder operator/(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::div());
    }

    friend ValueHolder operator>(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::greater());
    }

    friend ValueHolder operator<(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::less_or_equal());
    }

    friend ValueHolder operator>=(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::greater_or_equal());
    }

    friend ValueHolder operator<=(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::less_or_equal());
    }

    friend ValueHolder operator!=(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::not_equal());
    }

    friend ValueHolder operator==(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, ops::equal());
    }

    friend ValueHolder operator&&(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, [](auto &left, auto &right) -> decltype(auto) { return left && right; });
    }

    friend ValueHolder operator||(const ValueHolder &left, const ValueHolder &right) {
        return binaryOperator(left, right, [](auto &left, auto &right) -> decltype(auto) { return left || right; });
    }

    friend ValueHolder operator-(const ValueHolder &operand) {
        return unaryOperator(operand, ops::minus());
    }

    friend ValueHolder operator!(const ValueHolder &operand) {
        return unaryOperator(operand, ops::logical_not());
    }

    template<class OpType>
    friend ValueHolder binaryOperator(const ValueHolder &left, const ValueHolder &right, OpType op) {
        if (left.holds<PrimitiveValue>() && right.holds<PrimitiveValue>()) {
            return op(left.get<PrimitiveValue>(), right.get<PrimitiveValue>());
        } else if (left.holds<Vector>() && right.holds<Vector>()) {
            return op(left.get<Vector>(), right.get<Vector>());
        } else if (left.holds<Vector>() && right.holds<PrimitiveValue>()) {

            auto &leftV = left.get<Vector>();
            auto &rightP = right.get<PrimitiveValue>();

            Vector result;
            auto &resultMap = result.values;
            for (auto &it: leftV.keys()) {
                auto leftVal = leftV.get(it);
                resultMap->emplace(it, op(leftVal.value(), rightP));
            }
            return result;
        } else if (left.holds<PrimitiveValue>() && right.holds<Vector>()) {

            auto &leftP = left.get<PrimitiveValue>();
            auto &rightV = right.get<Vector>();

            Vector result;
            auto &resultMap = result.values;
            for (auto &it: rightV.keys()) {
                auto rightValue = rightV.get(it);
                resultMap->emplace(it, op(leftP, rightValue.value()));
            }
            return result;
        } else if (left.holds<VectorRef>()) {
            const auto &ref = left.get<VectorRef>();
            return binaryOperator(ref.get(0), right, op);
        } else if (right.holds<VectorRef>()) {
            const auto &ref = right.get<VectorRef>();
            return binaryOperator(left, ref.get(0), op);
        }
        throw std::runtime_error("unexpected operation");
    }

    template<class OpType>
    inline static ValueHolder unaryOperator(const ValueHolder &operand, OpType op) {
        if (operand.holds<PrimitiveValue>()) {
            return op(operand.get<PrimitiveValue>());
        } else if (operand.holds<Vector>()) {
            return op(operand.get<Vector>());
        } else if (operand.holds<VectorRef>()) {
            const auto &ref = operand.get<VectorRef>();
            return unaryOperator(ref.get(0), op);
        }
        throw std::runtime_error("unexpected operation");
    }

    inline Vector deRef() const {
        if (holds<Vector>()) {
            return get<Vector>();
        } else if (holds<VectorRef>()) {
            VectorRef ref = get<VectorRef>();
            return ref.get(0);
        }
        throw std::runtime_error("unexpected operation");
    }

private:
    std::shared_ptr<ValueBase> valuePtr;
};

std::string to_string(const ValueHolder &holder) ;

#endif //HUSKY_COMPUTE_VALUEBASE_H
