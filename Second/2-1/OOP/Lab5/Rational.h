#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <numeric>
#include <stdexcept>

template <typename T>
class Rational {
private:
    T numerator;   // Числитель
    T denominator; // Знаменатель

    // Приватная функция для сокращения дроби
    void reduce() {
        T gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        // Если знаменатель отрицательный, переносим знак в числитель
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Конструктор по умолчанию (создаёт 0/1)
    Rational() : numerator(0), denominator(1) {}

    // Конструктор с параметрами
    Rational(T num, T den) : numerator(num), denominator(den) {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    // Метод для отображения дроби
    void display() const {
        if (denominator == 1) {
            std::cout << numerator << std::endl;
        } else {
            std::cout << numerator << "/" << denominator << std::endl;
        }
    }

    // Арифметические операторы
    Rational operator+(const Rational& other) const {
        T num = numerator * other.denominator + other.numerator * denominator;
        T den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational operator-(const Rational& other) const {
        T num = numerator * other.denominator - other.numerator * denominator;
        T den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational operator*(const Rational& other) const {
        T num = numerator * other.numerator;
        T den = denominator * other.denominator;
        return Rational(num, den);
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Cannot divide by zero.");
        }
        T num = numerator * other.denominator;
        T den = denominator * other.numerator;
        return Rational(num, den);
    }
};

#endif // RATIONAL_H

