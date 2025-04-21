#include "Complex.h"
#include <cmath>
#include <sstream>
#include <regex>
#include <iostream>

// using namespace std::literals;

// Constructors
Complex::Complex() : re(0.0), im(0.0) {}

Complex::Complex(double real) : re(real), im(0.0) {}

Complex::Complex(double real, double imaginary) : re(real), im(imaginary) {}

Complex::Complex(const Complex &rhs) : re(rhs.re), im(rhs.im) {}

// Assignment operator
Complex& Complex::operator=(const Complex &rhs) {
    if (this != &rhs) {
        re = rhs.re;
        im = rhs.im;
    }
    return *this;
}

// Access methods
double Complex::real() const {
    return re;
}

double Complex::imag() const {
    return im;
}

// Compound assignment operators
Complex& Complex::operator+=(const Complex &rhs) {
    re += rhs.re;
    im += rhs.im;
    return *this;
}

Complex& Complex::operator-=(const Complex &rhs) {
    re -= rhs.re;
    im -= rhs.im;
    return *this;
}

Complex& Complex::operator*=(const Complex &rhs) {
    double temp_re = re * rhs.re - im * rhs.im;
    double temp_im = re * rhs.im + im * rhs.re;
    re = temp_re;
    im = temp_im;
    return *this;
}

Complex& Complex::operator/=(const Complex &rhs) {
    std::cout << " Run 6" << std::endl;
    // (a+bi) / (c+di) = (a+bi)*(c-di) / (c+di)*(c-di) = (ac+bd)/(c²+d²) + (bc-ad)/(c²+d²)i
    double denominator = rhs.re * rhs.re + rhs.im * rhs.im;
    double temp_re = (re * rhs.re + im * rhs.im) / denominator;
    double temp_im = (im * rhs.re - re * rhs.im) / denominator;

    re = temp_re;
    im = temp_im;
    
    
    return *this;
}


Complex& Complex::operator+=(double rhs) {
    re += rhs;
    return *this;
}

Complex& Complex::operator-=(double rhs) {
    re -= rhs;
    return *this;
}

Complex& Complex::operator*=(double rhs) {
    re *= rhs;
    im *= rhs;
    return *this;
}

Complex& Complex::operator/=(double rhs) {
    re /= rhs;
    im /= rhs;
    std::cout << " Run 2" << std::endl;

    return *this;
}

// Non-member functions

// Unary operators
Complex operator+(const Complex &z) {
    return z;
}

Complex operator-(const Complex &z) {
    return Complex(-z.real(), -z.imag());
}

// Binary arithmetic operators between two complex numbers
Complex operator+(const Complex &lhs, const Complex &rhs) {
    Complex result(lhs);
    result += rhs;
    return result;
}

Complex operator-(const Complex &lhs, const Complex &rhs) {
    Complex result(lhs);
    result -= rhs;
    return result;
}

Complex operator*(const Complex &lhs, const Complex &rhs) {
    Complex result(lhs);
    result *= rhs;
    return result;
}

Complex operator/(const Complex &lhs, const Complex &rhs) {
    Complex result(lhs);
    result /= rhs;
    std::cout << " Run 3" << std::endl;
    return result;
}

// Binary arithmetic operators with complex and scalar
Complex operator+(const Complex &lhs, double rhs) {
    Complex result(lhs);
    result += rhs;
    return result;
}

Complex operator+(double lhs, const Complex &rhs) {
    return Complex(lhs + rhs.real(), rhs.imag());
}

Complex operator-(const Complex &lhs, double rhs) {
    Complex result(lhs);
    result -= rhs;
    return result;
}

Complex operator-(double lhs, const Complex &rhs) {
    return Complex(lhs - rhs.real(), -rhs.imag());
}

Complex operator*(const Complex &lhs, double rhs) {
    Complex result(lhs);
    result *= rhs;
    return result;
}

Complex operator*(double lhs, const Complex &rhs) {
    return Complex(lhs * rhs.real(), lhs * rhs.imag());
}

Complex operator/(const Complex &lhs, double rhs) {
    Complex result(lhs);
    result /= rhs;
    std::cout << " Run 4" << std::endl;
    return result;
}

Complex operator/(double lhs, const Complex &rhs) {
    // lhs / rhs = lhs * conjugate(rhs) / (|rhs|²)
    double denominator = rhs.real() * rhs.real() + rhs.imag() * rhs.imag();
    std::cout << " Run 5" << std::endl;
    return Complex(
        lhs * rhs.real() / denominator,
        -lhs * rhs.imag() / denominator
    );
}

// Comparison operators
bool operator==(const Complex &lhs, const Complex &rhs) {
    return lhs.real() == rhs.real() && lhs.imag() == rhs.imag();
}

bool operator!=(const Complex &lhs, const Complex &rhs) {
    return !(lhs == rhs);
}

bool operator==(const Complex &lhs, double rhs) {
    return lhs.real() == rhs && lhs.imag() == 0.0;
}

bool operator==(double lhs, const Complex &rhs) {
    return lhs == rhs.real() && rhs.imag() == 0.0;
}

bool operator!=(const Complex &lhs, double rhs) {
    return !(lhs == rhs);
}

bool operator!=(double lhs, const Complex &rhs) {
    return !(lhs == rhs);
}

bool operator<(const Complex &lhs, const Complex &rhs) {
    return abs(lhs) < abs(rhs);
}

// Helper functions
double real(const Complex &z) {
    return z.real();
}

double imag(const Complex &z) {
    return z.imag();
}

double abs(const Complex &z) {
    return std::sqrt(z.real() * z.real() + z.imag() * z.imag());
}

// Stream operators
std::ostream& operator<<(std::ostream &os, const Complex &z) {
    os << "(" << z.real() << "," << z.imag() << ")";
    return os;
}

std::istream& operator>>(std::istream &is, Complex &z) {
    std::string input;
    is >> std::ws; // Skip leading whitespace
    std::getline(is, input);
    
    std::cout << "Input string: '" << input << "'" << std::endl;
    
    // Parse different formats:
    // 1. real
    // 2. (real)
    // 3. (real,imaginary)
    
    double real_part = 0.0;
    double imaginary_part = 0.0;
    
    // Format: (real,imaginary)
    std::regex complex_pattern(R"(\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*,\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*)");
    std::regex real_parens_pattern(R"(\s*\(\s*([-+]?[0-9]*\.?[0-9]+)\s*\)\s*)");
    std::smatch matches;
    if (std::regex_match(input, matches, complex_pattern)) {
        if (matches.size() == 3) {
            std::istringstream(matches[1].str()) >> real_part;
            std::istringstream(matches[2].str()) >> imaginary_part;
            z = Complex(real_part, imaginary_part);
            return is;
        }
    }
    
    // Format: (real)
    if (std::regex_match(input, matches, real_parens_pattern)) {
        if (matches.size() == 2) {
            std::istringstream(matches[1].str()) >> real_part;
            z = Complex(real_part, 0.0);
            return is;
        }
    }
    
    // Format: real
    try {
        real_part = std::stod(input);
        z = Complex(real_part, 0.0);
    } catch (...) {
        is.setstate(std::ios::failbit);
    }
    
    return is;
}

// Complex literal operators
Complex operator""_i(long double arg) {
    return Complex(0.0, static_cast<double>(arg));
}

Complex operator""_i(unsigned long long arg) {
    return Complex(0.0, static_cast<double>(arg));
}