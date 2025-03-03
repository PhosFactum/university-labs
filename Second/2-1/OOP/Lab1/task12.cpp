#include <iostream>
#include <numeric>  // for std::gcd in C++17

class Rational {
private:
    int numerator;   // numerator P
    int denominator; // denominator Q

    // Private function to reduce the fraction
    void reduce() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;

        // If the denominator is negative, move the sign to the numerator
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    // Default constructor (creates 0/1)
    Rational() : numerator(0), denominator(1) {}

    // Constructor with parameters
    Rational(int num, int den) : numerator(num), denominator(den) {
        if (den == 0) {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce(); // Reduce the fraction
    }

    // Display the rational number
    void display() const {
        if (denominator == 1) {
            std::cout << numerator << std::endl;
        } else {
            std::cout << numerator << "/" << denominator << std::endl;
        }
    }

    // Addition operator
    Rational operator+(const Rational& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    // Subtraction operator
    Rational operator-(const Rational& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    // Multiplication operator
    Rational operator*(const Rational& other) const {
        int num = numerator * other.numerator;
        int den = denominator * other.denominator;
        return Rational(num, den);
    }

    // Division operator
    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            throw std::invalid_argument("Cannot divide by zero.");
        }
        int num = numerator * other.denominator;
        int den = denominator * other.numerator;
        return Rational(num, den);
    }

    // Equality operator
    bool operator==(const Rational& other) const {
        return numerator == other.numerator && denominator == other.denominator;
    }

    // Inequality operator
    bool operator!=(const Rational& other) const {
        return !(*this == other);
    }

    // Less than operator
    bool operator<(const Rational& other) const {
        return numerator * other.denominator < other.numerator * denominator;
    }

    // Greater than operator
    bool operator>(const Rational& other) const {
        return numerator * other.denominator > other.numerator * denominator;
    }

    // Less than or equal to operator
    bool operator<=(const Rational& other) const {
        return !(*this > other);
    }

    // Greater than or equal to operator
    bool operator>=(const Rational& other) const {
        return !(*this < other);
    }
};

// Example usage of the Rational class
int main() {
    // Create two rational numbers
    Rational r1(2, 5);  // 2/5
    Rational r2(6, 8);  // 3/7

    // Display the original rational numbers
    std::cout << "Rational number 1: ";
    r1.display();
    std::cout << "Rational number 2: ";
    r2.display();
    std::cout << "\n";

    // Perform arithmetic operations
    Rational sum = r1 + r2;
    Rational diff = r1 - r2;
    Rational prod = r1 * r2;
    Rational quot = r1 / r2;

    // Display the results
    std::cout << "Sum: ";
    sum.display();
    std::cout << "Difference: ";
    diff.display();
    std::cout << "Product: ";
    prod.display();
    std::cout << "Quotient: ";
    quot.display();
    std::cout << "\n";

    // Compare the rational numbers
    std::cout << "\nComparing operations (0 - no, 1 - yes):" << std::endl;
    std::cout << "r1 == r2? Answer: " << (r1 == r2) << std::endl;
    std::cout << "r1 != r2? Answer: " << (r1 != r2) << std::endl;
    std::cout << "r1 < r2? Answer: " << (r1 < r2) << std::endl;
    std::cout << "r1 > r2? Answer: " << (r1 > r2) << std::endl;

    return 0;
}


// Change vector 2-dim array
