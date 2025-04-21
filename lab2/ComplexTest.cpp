#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include "Complex.h"

// Helper function to check if two complex numbers are approximately equal
bool approxEqual(const Complex& a, const Complex& b, double epsilon = 1e-10) {
    return std::abs(a.real() - b.real()) < epsilon && 
           std::abs(a.imag() - b.imag()) < epsilon;
}

// Define a testing function to print test results
void testCase(bool condition, const std::string& testName) {
    std::cout << (condition ? "PASS: " : "FAIL: ") << testName << std::endl;
}

int main() {
    // Set output precision
    std::cout << std::fixed << std::setprecision(6);
    
    std::cout << "==== BASIC INITIALIZATION TESTS ====" << std::endl;
    {
        // Test case 1: Default constructor
        Complex x;
        testCase(x.real() == 0.0 && x.imag() == 0.0, "Default constructor");
        
        // Test case 2: Constructor with real part
        Complex x2 = 5;
        testCase(x2.real() == 5.0 && x2.imag() == 0.0, "Constructor with real part");
        
        // Test case 3: Constructor with real and imaginary parts
        Complex y(6, 2);
        testCase(y.real() == 6.0 && y.imag() == 2.0, "Constructor with real and imaginary parts");
    }
    
    std::cout << "\n==== BASIC OPERATIONS TESTS ====" << std::endl;
    {
        // Test case 4: Addition
        Complex x;
        Complex y(6, 2);
        Complex z = x + y;
        testCase(z.real() == 6.0 && z.imag() == 2.0, "Complex + Complex");
        
        // Test case 5: Complex literal
        Complex k = 3 + 5_i;
        testCase(k.real() == 3.0 && k.imag() == 5.0, "Real + Complex literal");
        
        // Test case 6: Complex subtraction with literals
        k -= 5 + 1_i * Complex(5, 3);
        // 1_i * Complex(5, 3) = 0 + 1i * (5 + 3i) = 0 + 5i - 3
        // = -3 + 5i
        // 5 + (-3 + 5i) = 2 + 5i
        // k = 3 + 5i, k -= 2 + 5i = 1 + 0i
        testCase(approxEqual(k, Complex(1, 0)), "Complex subtraction with literals");
    }
    
    std::cout << "\n==== DIVISION TESTS ====" << std::endl;
    {
        // Test case 7: Complex / scalar
        Complex result = Complex(6, 6) / 6;
        testCase(approxEqual(result, Complex(1, 1)), "Complex / scalar");
        std::cout << "  Complex(6, 6) / 6 = " << result << std::endl;
        
        // Test case 8: Complex / Complex
        Complex a(4, 8);
        Complex b(2, 4);
        result = a / b;
        testCase(approxEqual(result, Complex(2, 0)), "Complex / Complex");
        std::cout << "  Complex(4, 8) / Complex(2, 4) = " << result << std::endl;
        
        // Test case 9: scalar / Complex
        result = 10.0 / Complex(2, 4);
        double denominator = 2*2 + 4*4;
        Complex expected(10*2/denominator, -10*4/denominator);
        testCase(approxEqual(result, expected), "scalar / Complex");
        std::cout << "  10.0 / Complex(2, 4) = " << result << std::endl;
        std::cout << "  Expected: " << expected << std::endl;
        
        // Test case 10: Division with pure imaginary number
        result = Complex(5, 5) / 5_i;
        testCase(approxEqual(result, Complex(1, -1)), "Complex / pure imaginary");
        std::cout << "  Complex(5, 5) / 5_i = " << result << std::endl;
        
        // Test case 11: Complex / 0 (check for division by zero handling)
        try {
            result = Complex(1, 1) / 0.0;
            std::cout << "  Complex(1, 1) / 0.0 = " << result << std::endl;
            // If we get here without exception, at least check if result contains infinity
            testCase(std::isinf(result.real()) || std::isinf(result.imag()), 
                    "Complex / 0 (expect infinity)");
        } catch (const std::exception& e) {
            std::cout << "  Complex(1, 1) / 0.0 threw exception: " << e.what() << std::endl;
            testCase(true, "Complex / 0 (exception handling)");
        }
    }
    
    std::cout << "\n==== CHAINING OPERATIONS TESTS ====" << std::endl;
    {
        // Test case 12: Chained addition
        Complex x;
        Complex y(1, 2);
        x = y + 1;
        testCase(approxEqual(x, Complex(2, 2)), "x = y + 1");
        
        // Test case 13: Multiple chained addition
        x = y + y + 1 + 5;
        // y + y = 2 + 4i
        // 2 + 4i + 1 = 3 + 4i
        // 3 + 4i + 5 = 8 + 4i
        testCase(approxEqual(x, Complex(8, 4)), "x = y + y + 1 + 5");
        
        // Test case 14: Scalar + Complex
        x = 2 + y;
        testCase(approxEqual(x, Complex(3, 2)), "x = 2 + y");
        
        // Test case 15: Chained += operator
        Complex a(1, 1);
        Complex b(2, 2);
        a += b += 4;
        // First: b += 4, so b becomes (6, 2)
        // Then: a += b, so a becomes (7, 3)
        testCase(approxEqual(b, Complex(6, 2)), "b += 4 (in chained expression)");
        testCase(approxEqual(a, Complex(7, 3)), "a += b += 4");
        
        // Test case 16: Chained assignment
        Complex c, d;
        c = d = 0;
        testCase(approxEqual(c, Complex(0, 0)) && approxEqual(d, Complex(0, 0)), "c = d = 0");
    }

    std::cout << "\n==== COMPLEX OPERATOR/= TESTS ====" << std::endl;
    {
        // Test operator/= with different values
        
        // Complex /= scalar
        Complex c1(6, 9);
        c1 /= 3;
        testCase(approxEqual(c1, Complex(2, 3)), "Complex /= scalar");

        // Complex /= scalar
        Complex c9(2, 2);
        c9 /= 2_i;
        testCase(approxEqual(c9, Complex(1, -1)), "Complex /= scalar");
        std::cout << "  c9 = " << c9 << std::endl;
        
        // Complex /= Complex
        Complex c2(10, 20);
        Complex c3(5, 5);
        c2 /= c3;
        double denominator = 5*5 + 5*5;
        double real_part = (10*5 + 20*5) / denominator;
        double imag_part = (20*5 - 10*5) / denominator;
        testCase(approxEqual(c2, Complex(real_part, imag_part)), "Complex /= Complex");
        std::cout << "  (10 + 20i) /= (5 + 5i) = " << c2 << std::endl;
        
        // Chaining division
        Complex c4(8, 16);
        Complex c5(2, 0);
        Complex c6(2, 0);
        c4 /= c5 /= c6;
        // First: c5 /= c6, so c5 becomes (1, 0)
        // Then: c4 /= c5, so c4 becomes (8, 16)
        testCase(approxEqual(c5, Complex(1, 0)), "c5 /= c6");
        testCase(approxEqual(c4, Complex(8, 16)), "c4 /= c5 /= c6");
    }
    
    return 0;
}