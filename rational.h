#pragma once

#include <iostream>
#include <numeric> 
#include <stdexcept> 
#include <cassert> 

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {
        Reduction();
    }

    Rational(int numerator) : numerator_(numerator), denominator_(1) {
        Reduction();
    }

    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        Reduction();
    }

    Rational(const Rational& other) : numerator_(other.numerator_), denominator_(other.denominator_) {
        Reduction();
    }

    Rational& operator=(const Rational& other) {
        if (this != &other) {
            numerator_ = other.numerator_;
            denominator_ = other.denominator_;
            Reduction();
        }
        return *this;
    }

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational Inv() const {
        if (numerator_ == 0) {
            throw std::invalid_argument("Cannot invert zero");
        }
        return Rational(denominator_, numerator_);
    }

    Rational operator+(const Rational& r2) const {
        Rational result = *this;
        result += r2;
        return result;
    }

    Rational operator-(const Rational& r2) const {
        Rational result = *this;
        result -= r2;
        return result;
    }

    Rational operator*(const Rational& r2) const {
        Rational result = *this;
        result *= r2;
        return result;
    }

    Rational operator/(const Rational& r2) const {
        if (r2.numerator_ == 0) {
            throw std::invalid_argument("Division by zero");
        }
        Rational result = *this;
        result /= r2;
        return result;
    }

    Rational& operator+=(const Rational& r2) {
        numerator_ = numerator_ * r2.denominator_ + r2.numerator_ * denominator_;
        denominator_ *= r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r2) {
        numerator_ = numerator_ * r2.denominator_ - r2.numerator_ * denominator_;
        denominator_ *= r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& r2) {
        numerator_ *= r2.numerator_;
        denominator_ *= r2.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r2) {
        if (r2.numerator_ == 0) {
            throw std::invalid_argument("Division by zero");
        }
        numerator_ *= r2.denominator_;
        denominator_ *= r2.numerator_;
        Reduction();
        return *this;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    bool operator==(const Rational& r) const {
        return numerator_ == r.numerator_ && denominator_ == r.denominator_;
    }

    bool operator!=(const Rational& r) const {
        return !(*this == r);
    }

    bool operator<(const Rational& r) const {
        return numerator_ * r.denominator_ < r.numerator_ * denominator_;
    }

    bool operator<=(const Rational& r) const {
        return *this < r || *this == r;
    }

    bool operator>(const Rational& r) const {
        return !(*this <= r);
    }

    bool operator>=(const Rational& r) const {
        return !(*this < r);
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        if (r.denominator_ == 1) {
            os << r.numerator_;
        } else {
            os << r.numerator_ << " / " << r.denominator_;
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rational& r) {
        int numerator, denominator = 1;
        char slash;
        
        if (is >> numerator) {
            if (is >> slash && slash == '/') {
                is >> denominator;
                if (denominator == 0) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
            }
            Rational temp(numerator, denominator);
            r = temp;
        } else {
            is.setstate(std::ios::failbit);
        }
        return is;
    }

private:
    int numerator_;
    int denominator_;

    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        int gcd = std::gcd(numerator_, denominator_);
        numerator_ /= gcd;
        denominator_ /= gcd;
    }
};