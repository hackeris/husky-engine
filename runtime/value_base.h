//
// Created by rainm on 2021/1/2.
//

#ifndef HUSKY_ENGINE_VALUEBASE_H
#define HUSKY_ENGINE_VALUEBASE_H

#include <set>
#include <map>
#include <string>
#include <memory>
#include <functional>
#include <optional>
#include <utility>
#include <variant>
#include <cassert>

#include <cmath>

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

class value_base {
public:
    template<typename T>
    [[nodiscard]] inline bool is() const {
        auto *ptr = dynamic_cast<const T *>(this);
        return ptr != nullptr;
    }

    template<typename T>
    [[nodiscard]] inline const T &as() const {
        auto *ptr = dynamic_cast<const T *>(this);
        assert(ptr != nullptr);
        return *ptr;
    }

    value_base() = default;

    virtual ~value_base() = default;
};

class primitive : public value_base {
public:
    template<typename value_type>
    primitive(value_type value):value(value) {} // NOLINT(google-explicit-constructor)

    primitive(const primitive &) = default;

    friend inline primitive operator+(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::add());
    }

    friend inline primitive operator-(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::sub());
    }

    friend inline primitive operator*(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::multi());
    }

    friend inline primitive operator/(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::div());
    }

    friend inline primitive operator>(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::greater());
    }

    friend inline primitive operator<(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::less());
    }

    friend inline primitive operator>=(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::greater_or_equal());
    }

    friend inline primitive operator<=(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::less_or_equal());
    }

    friend inline primitive operator!=(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::not_equal());
    }

    friend inline primitive operator==(const primitive &left, const primitive &right) {
        return binary_operator<>(left, right, ops::equal());
    }

    friend inline primitive operator&&(const primitive &left, const primitive &right) {
        if (left.holds<bool>() && right.holds<bool>()) {
            return primitive(left.get<bool>() && right.get<bool>());
        }
        throw std::runtime_error("unexpected type on operator");
    }

    friend inline primitive operator||(const primitive &left, const primitive &right) {
        if (left.holds<bool>() && right.holds<bool>()) {
            return primitive(left.get<bool>() || right.get<bool>());
        }
        throw std::runtime_error("unexpected type on operator");
    }

    friend inline primitive operator-(const primitive &operand) {
        return unary_operator(operand, ops::minus());
    }

    friend inline primitive operator!(const primitive &operand) {
        return unary_operator(operand, ops::logical_not());
    }

    friend inline primitive power(const primitive &left, const primitive &right) {
        if (left.holds<int>() && right.holds<int>()) {
            return primitive((int) round(pow(left.get<int>(), right.get<int>())));
        } else if (left.holds<float>() || right.holds<float>()) {
            float left_ = left.holds<float>() ? left.get<float>() : (float) left.get<int>();
            float right_ = right.holds<float>() ? right.get<float>() : (float) right.get<int>();
            return primitive((float) pow(left_, right_));
        }
        throw std::runtime_error("unexpected type on operator");
    }

    template<typename V>
    [[nodiscard]] inline bool holds() const {
        return std::holds_alternative<V>(value);
    }

    template<typename V>
    [[nodiscard]] inline V get() const {
        return std::get<V>(value);
    }

private:

    template<class OP>
    inline static primitive binary_operator(
            const primitive &left, const primitive &right, OP op) {

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

    template<class OP>
    inline static primitive unary_operator(const primitive &value, OP op) {
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

class vector : public value_base {
public:
    vector() : values(std::make_shared<std::map<std::string, primitive>>()) {}

    vector(std::map<std::string, primitive> &&values)
            : values(std::make_shared<std::map<std::string, primitive>>(values)) {}

    friend vector operator+(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::add());
    }

    friend vector operator-(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::sub());
    }

    friend vector operator*(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::multi());
    }

    friend vector operator/(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::div());
    }

    friend vector operator>(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::greater());
    }

    friend vector operator<(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::less());
    }

    friend vector operator>=(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::greater_or_equal());
    }

    friend vector operator<=(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::less_or_equal());
    }

    friend vector operator!=(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::not_equal());
    }

    friend vector operator==(const vector &left, const vector &right) {
        return binary_operator(left, right, ops::equal());
    }

    friend vector operator||(const vector &left, const vector &right) {
        return binary_operator(left, right,
                               [](auto &left, auto &right) -> decltype(auto) { return left || right; });
    }

    friend vector operator&&(const vector &left, const vector &right) {
        return binary_operator(left, right,
                               [](auto &left, auto &right) -> decltype(auto) { return left && right; });
    }

    friend vector operator-(const vector &operand) {
        return unary_operator(operand, ops::minus());
    }

    friend vector operator!(const vector &operand) {
        return unary_operator(operand, ops::logical_not());
    }

    template<class OpType>
    inline static vector binary_operator(const vector &left, const vector &right, OpType op) {

        std::set<std::string> left_keys = left.keys()
        , right_keys = right.keys();

        std::set<std::string> all_keys;
        std::set_union(left_keys.begin(), left_keys.end(),
                       right_keys.begin(), right_keys.end(),
                       std::inserter(all_keys, all_keys.begin()));

        vector result;
        for (auto &it: all_keys) {
            if (left.contains(it) && right.contains(it)) {
                auto left_ = left.get(it);
                auto right_ = right.get(it);
                result.put(it, op(left_.value(), right_.value()));
            }
        }
        return result;
    }

    template<class OpType>
    inline static vector unary_operator(const vector &operand, OpType op) {

        std::set<std::string> allKeys = operand.keys();

        vector result;
        for (auto &it: allKeys) {
            auto operand_ = operand.get(it);
            result.put(it, op(operand_.value()));
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

    inline void put(std::string &&label, primitive &&value) {
        values->emplace(label, value);
    }

    inline void put(const std::string &label, const primitive &value) {
        values->emplace(label, value);
    }

    [[nodiscard]]
    const std::map<std::string, primitive> &getValues() const {
        return *values;
    }

    [[nodiscard]]
    inline std::optional<primitive> get(const std::string &label) const {
        auto iter = values->find(label);
        if (iter != values->end()) {
            return std::optional<primitive>((*iter).second);
        }
        return std::nullopt;
    }

private:
    std::shared_ptr<std::map<std::string, primitive>> values;
};

class vector_ref : public value_base {
public:
    explicit vector_ref(std::function<vector(int)> getter) : getter(std::move(getter)) {}

    [[nodiscard]]
    inline vector get(int index) const {
        return getter(index);
    }

private:
    std::function<vector(int)> getter;
};

class value_holder {
public:
    template<typename V>
    value_holder(const V &value)
            :val_ptr(std::make_shared<V>(std::move(value))) {}

public:
    template<typename T>
    [[nodiscard]] inline bool holds() const {
        const T *ptr = dynamic_cast<const T *>(val_ptr.get());
        return ptr != nullptr;
    }

    template<typename T>
    [[nodiscard]] inline const T &get() const {
        return *std::dynamic_pointer_cast<T>(val_ptr);
    }

    friend value_holder operator+(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::add());
    }

    friend value_holder operator-(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::sub());
    }

    friend value_holder operator*(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::multi());
    }

    friend value_holder operator/(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::div());
    }

    friend value_holder operator>(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::greater());
    }

    friend value_holder operator<(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::less_or_equal());
    }

    friend value_holder operator>=(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::greater_or_equal());
    }

    friend value_holder operator<=(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::less_or_equal());
    }

    friend value_holder operator!=(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::not_equal());
    }

    friend value_holder operator==(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, ops::equal());
    }

    friend value_holder operator&&(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, [](auto &left, auto &right) -> decltype(auto) { return left && right; });
    }

    friend value_holder operator||(const value_holder &left, const value_holder &right) {
        return binary_operator(left, right, [](auto &left, auto &right) -> decltype(auto) { return left || right; });
    }

    friend value_holder operator-(const value_holder &operand) {
        return unary_operator(operand, ops::minus());
    }

    friend value_holder operator!(const value_holder &operand) {
        return unary_operator(operand, ops::logical_not());
    }

    template<class OpType>
    friend value_holder binary_operator(const value_holder &left, const value_holder &right, OpType op) {
        if (left.holds<primitive>() && right.holds<primitive>()) {
            return op(left.get<primitive>(), right.get<primitive>());
        } else if (left.holds<vector>() && right.holds<vector>()) {
            return op(left.get<vector>(), right.get<vector>());
        } else if (left.holds<vector>() && right.holds<primitive>()) {

            auto &left_ = left.get<vector>();
            auto &right_ = right.get<primitive>();

            vector result;
            for (auto &it: left_.keys()) {
                auto leftVal = left_.get(it);
                result.put(it, op(leftVal.value(), right_));
            }
            return result;
        } else if (left.holds<primitive>() && right.holds<vector>()) {

            auto &left_ = left.get<primitive>();
            auto &right_ = right.get<vector>();

            vector result;
            for (auto &it: right_.keys()) {
                auto right_val = right_.get(it);
                result.put(it, op(left_, right_val.value()));
            }
            return result;
        } else if (left.holds<vector_ref>()) {
            const auto &ref = left.get<vector_ref>();
            return binary_operator(ref.get(0), right, op);
        } else if (right.holds<vector_ref>()) {
            const auto &ref = right.get<vector_ref>();
            return binary_operator(left, ref.get(0), op);
        }
        throw std::runtime_error("unexpected operation");
    }

    template<class OpType>
    inline static value_holder unary_operator(const value_holder &operand, OpType op) {
        if (operand.holds<primitive>()) {
            return op(operand.get<primitive>());
        } else if (operand.holds<vector>()) {
            return op(operand.get<vector>());
        } else if (operand.holds<vector_ref>()) {
            const auto &ref = operand.get<vector_ref>();
            return unary_operator(ref.get(0), op);
        }
        throw std::runtime_error("unexpected operation");
    }

    inline vector de_ref() const {
        if (holds<vector>()) {
            return get<vector>();
        } else if (holds<vector_ref>()) {
            vector_ref ref = get<vector_ref>();
            return ref.get(0);
        }
        throw std::runtime_error("unexpected operation");
    }

private:
    std::shared_ptr<value_base> val_ptr;
};


#endif //HUSKY_ENGINE_VALUEBASE_H
