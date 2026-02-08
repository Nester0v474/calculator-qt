#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <sstream>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template<typename Number>
class Calculator {

public:

    void Set(Number n) {
        result_ = n;
    }

    Number GetNumber() const {
        return result_;
    }

    std::optional<Error> Add(Number n) {
        result_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number n) {
        result_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Div(Number n) {
        if constexpr (std::is_same_v<Number, Rational>) {
            if (n.GetNumerator() == 0) {
                return Error{"Division by zero"};
            }
        }
        else if constexpr (std::is_integral_v<Number>){
            if (n == 0) {
                return Error{"Division by zero"};
            }
        }
        result_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number n) {
        result_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number n) {
        if constexpr (std::is_same_v<Number, Rational>) {
            if (n.GetNumerator() == 0 && result_.GetNumerator() == 0) {
                return Error{"Zero power to zero"};
            }
            else if (n.GetDenominator() != 1) {
                return Error{"Fractional power is not supported"};
            }
            else {
                result_ = ::Pow(result_, n);
                return std::nullopt;
            }
        }
        else if constexpr (std::is_integral_v<Number>) {
            if (n == 0 && result_ == 0) {
                return Error{"Zero power to zero"};
            }
            else if (n < 0) {
                return Error{"Integer negative power"};
            }
            else {
                result_ = IntegerPow(result_, n);
                return std::nullopt;
            }
        }
        else {
            result_ = std::pow(result_, n);
            return std::nullopt;
        }

    }

    void Save() {
        mem_ = result_;
    }

    void Load() {
        if (mem_.has_value()) {
            result_ = mem_.value();
        }
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

   std::string GetNumberRepr() const {
    std::stringstream ss;
    if constexpr (std::is_same_v<Number, Rational>) {
        ss << result_; 
    } else {
        ss << result_;
    }
    return ss.str();
}

private:

    Number result_ = 0;
    std::optional<Number> mem_ = std::nullopt;

};