#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <sstream>
#include <vector>
#include "Complex.h"

// Helper function to compare double values with tolerance
bool approxEqual(double a, double b, double epsilon = 1e-10) {
    return std::abs(a - b) < epsilon;
}

// Helper function to compare complex values with tolerance
bool approxEqual(const Complex& a, const Complex& b, double epsilon = 1e-10) {
    return approxEqual(a.real(), b.real(), epsilon) && 
           approxEqual(a.imag(), b.imag(), epsilon);
}

// Function to print a complex number with high precision
void printComplex(const Complex& c, const std::string& label) {
    std::cout << std::setprecision(15) << label << ": " 
              << "(" << c.real() << ", " << c.imag() << ")" << std::endl;
}

int main() {
    std::cout << "RUNNING DETAILED COMPLEX NUMBER BUG FINDER" << std::endl;
    std::cout << "=========================================" << std::endl;
    
    int failCount = 0;
    
    // Special attention to division operations
    std::cout << "\nTESTING DIVISION OPERATIONS:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    
    // Test case 1: Simple division
    {
        Complex a(4.0, 2.0);
        Complex b(2.0, 1.0);
        Complex result = a / b;
        Complex expected(2.0, 0.0);
        
        printComplex(a, "a");
        printComplex(b, "b");
        printComplex(result, "a / b (actual)");
        printComplex(expected, "a / b (expected)");
        
        if (!approxEqual(result, expected)) {
            std::cout << "ERROR: Simple division failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 2: Division with pure imaginary number
    {
        Complex a(3.0, 4.0);
        Complex b(0.0, 2.0);
        Complex result = a / b;
        Complex expected(2.0, -1.5);  
        
        printComplex(a, "a");
        printComplex(b, "b (pure imaginary)");
        printComplex(result, "a / b (actual)");
        printComplex(expected, "a / b (expected)");
        
        if (!approxEqual(result, expected)) {
            std::cout << "ERROR: Division by pure imaginary failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 3: Division of pure real by complex
    {
        Complex a(5.0, 0.0);
        Complex b(3.0, 4.0);
        Complex result = a / b;
        double denominator = b.real() * b.real() + b.imag() * b.imag();
        Complex expected(5.0 * b.real() / denominator, -5.0 * b.imag() / denominator);
        
        printComplex(a, "a (pure real)");
        printComplex(b, "b");
        printComplex(result, "a / b (actual)");
        printComplex(expected, "a / b (expected)");
        
        if (!approxEqual(result, expected)) {
            std::cout << "ERROR: Division of pure real by complex failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 4: Scalar division by complex
    {
        double scalar = 10.0;
        Complex b(2.0, 4.0);
        Complex result = scalar / b;
        double denominator = b.real() * b.real() + b.imag() * b.imag();
        Complex expected(scalar * b.real() / denominator, -scalar * b.imag() / denominator);
        
        std::cout << "scalar: " << scalar << std::endl;
        printComplex(b, "b");
        printComplex(result, "scalar / b (actual)");
        printComplex(expected, "scalar / b (expected)");
        
        if (!approxEqual(result, expected)) {
            std::cout << "ERROR: Scalar division by complex failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 5: Division by scalar
    {
        Complex a(6.0, 8.0);
        double scalar = 2.0;
        Complex result = a / scalar;
        Complex expected(3.0, 4.0);
        
        printComplex(a, "a");
        std::cout << "scalar: " << scalar << std::endl;
        printComplex(result, "a / scalar (actual)");
        printComplex(expected, "a / scalar (expected)");
        
        if (!approxEqual(result, expected)) {
            std::cout << "ERROR: Division by scalar failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test known problematic cases
    std::cout << "\nTESTING COMPLEX FORMULAS AND IDENTITIES:" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    
    // Test case 6: Euler's identity formula for complex numbers
    {
        Complex a(1.0, 1.0);
        Complex b(1.0, 1.0);
        Complex one(1.0, 0.0);
        
        // Testing (a / b) * b = a
        Complex division_result = a / b;
        Complex multiplication_result = division_result * b;
        
        printComplex(a, "a");
        printComplex(b, "b");
        printComplex(division_result, "a / b");
        printComplex(multiplication_result, "(a / b) * b (should equal a)");
        
        if (!approxEqual(multiplication_result, a)) {
            std::cout << "ERROR: Division/multiplication identity failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 7: Check associativity of multiplication
    {
        Complex a(2.0, 3.0);
        Complex b(4.0, -1.0);
        Complex c(0.0, 2.0);
        
        Complex result1 = (a * b) * c;
        Complex result2 = a * (b * c);
        
        printComplex(result1, "(a * b) * c");
        printComplex(result2, "a * (b * c)");
        
        if (!approxEqual(result1, result2)) {
            std::cout << "ERROR: Multiplication is not associative!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 8: Distributive property
    {
        Complex a(1.0, 2.0);
        Complex b(3.0, 4.0);
        Complex c(5.0, 6.0);
        
        Complex result1 = a * (b + c);
        Complex result2 = a * b + a * c;
        
        printComplex(result1, "a * (b + c)");
        printComplex(result2, "a * b + a * c");
        
        if (!approxEqual(result1, result2)) {
            std::cout << "ERROR: Distributive property failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test scalar and complex mixed operations
    std::cout << "\nTESTING MIXED SCALAR AND COMPLEX OPERATIONS:" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    
    // Test case 9: (scalar + complex) / complex
    {
        double scalar = 3.0;
        Complex a(2.0, 1.0);
        Complex b(1.0, 2.0);
        
        Complex result1 = (scalar + a) / b;
        Complex result2 = scalar / b + a / b;
        
        std::cout << "scalar: " << scalar << std::endl;
        printComplex(a, "a");
        printComplex(b, "b");
        printComplex(result1, "(scalar + a) / b");
        printComplex(result2, "scalar / b + a / b");
        
        if (!approxEqual(result1, result2)) {
            std::cout << "ERROR: Mixed operation (scalar + complex) / complex failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 10: complex / (scalar * complex)
    {
        Complex a(4.0, 5.0);
        double scalar = 2.0;
        Complex b(1.0, 3.0);
        
        Complex result1 = a / (scalar * b);
        Complex result2 = a / scalar / b;
        
        printComplex(a, "a");
        std::cout << "scalar: " << scalar << std::endl;
        printComplex(b, "b");
        printComplex(result1, "a / (scalar * b)");
        printComplex(result2, "a / scalar / b");
        
        if (!approxEqual(result1, result2)) {
            std::cout << "ERROR: Mixed operation complex / (scalar * complex) failed!" << std::endl;
            failCount++;
        }
    }
    
    // Test case 11: operator==, operator!=
    {
        Complex a(1.0, 2.0);
        Complex b(1.0, 2.0);
        Complex c(1.0, 2.00000001);
        
        if (!(a == b)) {
            std::cout << "ERROR: operator== failed for equal complex numbers!" << std::endl;
            failCount++;
        }
        
        if (a != b) {
            std::cout << "ERROR: operator!= failed for equal complex numbers!" << std::endl;
            failCount++;
        }
        
        if (a == c) {
            std::cout << "ERROR: operator== failed for slightly different complex numbers!" << std::endl;
            failCount++;
        }
    }
    
    // Test complex division scenarios that often cause bugs
    std::cout << "\nTESTING EDGE CASES FOR DIVISION:" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    
    // Test case 12: Division with very small denominator
    {
        Complex a(1.0, 1.0);
        Complex b(1e-10, 1e-10);
        Complex result = a / b;
        
        double denominator = b.real() * b.real() + b.imag() * b.imag();
        Complex expected((a.real() * b.real() + a.imag() * b.imag()) / denominator,
                       (a.imag() * b.real() - a.real() * b.imag()) / denominator);
        
        printComplex(a, "a");
        printComplex(b, "b (very small)");
        printComplex(result, "a / b (actual)");
        printComplex(expected, "a / b (expected)");
        
        if (!approxEqual(result, expected, 1e-5)) {  // Using a larger epsilon due to potential floating point issues
            std::cout << "ERROR: Division with very small denominator failed!" << std::endl;
            failCount++;
        }
    }
    
    std::cout << "\nSUMMARY:" << std::endl;
    std::cout << "-------" << std::endl;
    if (failCount == 0) {
        std::cout << "All tests passed successfully!" << std::endl;
    } else {
        std::cout << "Found " << failCount << " potential issues in the implementation." << std::endl;
    }
    
    return failCount;
}