#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <string>

class Complex {
private:
    double re;  // Real part
    double im;  // Imaginary part

public:
    // Constructors
    Complex();
    Complex(double real);  // Non-explicit to allow z = 3
    Complex(double real, double imaginary);
    Complex(const Complex &rhs);

    // Assignment operator
    Complex& operator=(const Complex &rhs);
    
    // Access methods
    double real() const;
    double imag() const;
    
    // Compound assignment operators
    Complex& operator+=(const Complex &rhs);
    Complex& operator-=(const Complex &rhs);
    Complex& operator*=(const Complex &rhs);
    Complex& operator/=(const Complex &rhs);
    Complex& operator+=(double rhs);
    Complex& operator-=(double rhs);
    Complex& operator*=(double rhs);
    Complex& operator/=(double rhs);
};

// Non-member functions

// Unary operators
Complex operator+(const Complex &z);
Complex operator-(const Complex &z);

// Binary arithmetic operators
Complex operator+(const Complex &lhs, const Complex &rhs);
Complex operator-(const Complex &lhs, const Complex &rhs);
Complex operator*(const Complex &lhs, const Complex &rhs);
Complex operator/(const Complex &lhs, const Complex &rhs);

// Complex and scalar operations
Complex operator+(const Complex &lhs, double rhs);
Complex operator+(double lhs, const Complex &rhs);
Complex operator-(const Complex &lhs, double rhs);
Complex operator-(double lhs, const Complex &rhs);
Complex operator*(const Complex &lhs, double rhs);
Complex operator*(double lhs, const Complex &rhs);
Complex operator/(const Complex &lhs, double rhs);
Complex operator/(double lhs, const Complex &rhs);

// Comparison operators
bool operator==(const Complex &lhs, const Complex &rhs);
bool operator!=(const Complex &lhs, const Complex &rhs);
bool operator==(const Complex &lhs, double rhs);
bool operator==(double lhs, const Complex &rhs);
bool operator!=(const Complex &lhs, double rhs);
bool operator!=(double lhs, const Complex &rhs);
bool operator<(const Complex &lhs, const Complex &rhs);

// Stream operators
std::ostream& operator<<(std::ostream &os, const Complex &z);
std::istream& operator>>(std::istream &is, Complex &z);

// Helper functions
double real(const Complex &z);
double imag(const Complex &z);
double abs(const Complex &z);

// Complex literal operators
Complex operator""_i(long double arg);
Complex operator""_i(unsigned long long arg);

#endif // COMPLEX_H