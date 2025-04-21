#include "Complex.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>

// Helper function for approximately equal
bool approx_equal(double a, double b, double epsilon = 1e-10) {
    return std::abs(a - b) < epsilon;
}

bool approx_equal(const Complex& a, const Complex& b, double epsilon = 1e-10) {
    return approx_equal(a.real(), b.real(), epsilon) && 
           approx_equal(a.imag(), b.imag(), epsilon);
}

int main() {
    std::cout << "Extended Testing of Complex class..." << std::endl;

    // Boundary Values
    Complex large(1e308, 1e308);
    Complex small(1e-308, 1e-308);
    assert(approx_equal(large + small, large));

    // Negative Values
    Complex neg(-5, -5);
    assert(approx_equal(neg + Complex(5, 5), Complex(0, 0)));

    // Zero Values
    Complex zero(0, 0);
    assert(approx_equal(zero * large, zero));

    // Complex Arithmetic
    Complex a(1, 1);
    Complex b(2, 2);
    Complex c = (a + b) * Complex(0, 1);
    assert(approx_equal(c, Complex(-3, 3)));

    // Comparison Operators
    assert(Complex(1, 1) == Complex(1, 1));
    assert(Complex(1, 1) != Complex(1, 0));
    assert(!(Complex(1, 1) < Complex(1, 1)));
    assert(Complex(1, 1) < Complex(2, 2));

    // Stream Input/Output
    std::istringstream iss("(3.14, 2.71)");
    Complex input;
    iss >> input;
    assert(approx_equal(input, Complex(3.14, 2.71)));

    std::ostringstream oss;
    oss << input;
    assert(oss.str() == "(3.14,2.71)");

    std::cout << "All extended tests passed!" << std::endl;
    return 0;
} 