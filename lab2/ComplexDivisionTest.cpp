#include <iostream>
#include <iomanip>
#include <cmath>
#include "Complex.h"

// Helper function for comparing doubles with tolerance
bool approxEqual(double a, double b, double epsilon = 1e-10) {
    return std::abs(a - b) < epsilon;
}

// Helper function to print complex numbers with high precision
void printComplex(const Complex& c, const std::string& label) {
    std::cout << std::fixed << std::setprecision(15);
    std::cout << label << ": (" << c.real() << ", " << c.imag() << ")" << std::endl;
}

// Manual calculation of complex division for verification
Complex manualDivide(const Complex& a, const Complex& b) {
    double denominator = b.real() * b.real() + b.imag() * b.imag();
    double real_part = (a.real() * b.real() + a.imag() * b.imag()) / denominator;
    double imag_part = (a.imag() * b.real() - a.real() * b.imag()) / denominator;
    return Complex(real_part, imag_part);
}

int main() {
    std::cout << "COMPLEX DIVISION DETAILED TEST" << std::endl;
    std::cout << "=============================" << std::endl;
    
    // Case 1: Standard complex division
    {
        std::cout << "\nTest Case 1: Standard complex division" << std::endl;
        Complex a(3.0, 4.0);
        Complex b(1.0, 2.0);
        
        printComplex(a, "a");
        printComplex(b, "b");
        
        Complex result = a / b;
        Complex expected = manualDivide(a, b);
        
        printComplex(result, "a / b (using operator/)");
        printComplex(expected, "a / b (manual calculation)");
        
        if (!approxEqual(result.real(), expected.real()) || !approxEqual(result.imag(), expected.imag())) {
            std::cout << "ERROR: Division calculation mismatch!" << std::endl;
            std::cout << "Difference: real=" << result.real() - expected.real() 
                      << ", imag=" << result.imag() - expected.imag() << std::endl;
        } else {
            std::cout << "PASS: Division calculations match." << std::endl;
        }
        
        // Verification: (a/b) * b should equal a
        Complex verification = result * b;
        printComplex(verification, "(a/b) * b (should equal a)");
        
        if (!approxEqual(verification.real(), a.real()) || !approxEqual(verification.imag(), a.imag())) {
            std::cout << "ERROR: Verification failed! (a/b) * b != a" << std::endl;
        } else {
            std::cout << "PASS: Verification (a/b) * b = a" << std::endl;
        }
    }
    
    // Case 2: Division by pure imaginary number
    {
        std::cout << "\nTest Case 2: Division by pure imaginary number" << std::endl;
        Complex a(3.0, 4.0);
        Complex b(0.0, 2.0);
        
        printComplex(a, "a");
        printComplex(b, "b (pure imaginary)");
        
        Complex result = a / b;
        Complex expected = manualDivide(a, b);
        
        printComplex(result, "a / b (using operator/)");
        printComplex(expected, "a / b (manual calculation)");
        
        if (!approxEqual(result.real(), expected.real()) || !approxEqual(result.imag(), expected.imag())) {
            std::cout << "ERROR: Division by pure imaginary calculation mismatch!" << std::endl;
            std::cout << "Difference: real=" << result.real() - expected.real() 
                      << ", imag=" << result.imag() - expected.imag() << std::endl;
        } else {
            std::cout << "PASS: Division by pure imaginary calculations match." << std::endl;
        }
        
        // Verification: (a/b) * b should equal a
        Complex verification = result * b;
        printComplex(verification, "(a/b) * b (should equal a)");
        
        if (!approxEqual(verification.real(), a.real()) || !approxEqual(verification.imag(), a.imag())) {
            std::cout << "ERROR: Verification failed! (a/b) * b != a" << std::endl;
        } else {
            std::cout << "PASS: Verification (a/b) * b = a" << std::endl;
        }
    }
    
    // Case 3: Division of scalar by complex
    {
        std::cout << "\nTest Case 3: Division of scalar by complex" << std::endl;
        double scalar = 5.0;
        Complex b(3.0, 4.0);
        
        std::cout << "scalar: " << scalar << std::endl;
        printComplex(b, "b");
        
        Complex result = scalar / b;
        double denominator = b.real() * b.real() + b.imag() * b.imag();
        Complex expected(scalar * b.real() / denominator, -scalar * b.imag() / denominator);
        
        printComplex(result, "scalar / b (using operator/)");
        printComplex(expected, "scalar / b (manual calculation)");
        
        if (!approxEqual(result.real(), expected.real()) || !approxEqual(result.imag(), expected.imag())) {
            std::cout << "ERROR: Scalar division by complex calculation mismatch!" << std::endl;
            std::cout << "Difference: real=" << result.real() - expected.real() 
                      << ", imag=" << result.imag() - expected.imag() << std::endl;
        } else {
            std::cout << "PASS: Scalar division by complex calculations match." << std::endl;
        }
        
        // Verification: (scalar/b) * b should equal scalar
        Complex verification = result * b;
        printComplex(verification, "(scalar/b) * b (should equal scalar)");
        
        if (!approxEqual(verification.real(), scalar) || !approxEqual(verification.imag(), 0.0)) {
            std::cout << "ERROR: Verification failed! (scalar/b) * b != scalar" << std::endl;
        } else {
            std::cout << "PASS: Verification (scalar/b) * b = scalar" << std::endl;
        }
    }
    
    // Case 4: Division of complex by complex with small values
    {
        std::cout << "\nTest Case 4: Division with small values" << std::endl;
        Complex a(0.0003, 0.0004);
        Complex b(0.0001, 0.0002);
        
        printComplex(a, "a (small values)");
        printComplex(b, "b (small values)");
        
        Complex result = a / b;
        Complex expected = manualDivide(a, b);
        
        printComplex(result, "a / b (using operator/)");
        printComplex(expected, "a / b (manual calculation)");
        
        if (!approxEqual(result.real(), expected.real()) || !approxEqual(result.imag(), expected.imag())) {
            std::cout << "ERROR: Division with small values calculation mismatch!" << std::endl;
            std::cout << "Difference: real=" << result.real() - expected.real() 
                      << ", imag=" << result.imag() - expected.imag() << std::endl;
        } else {
            std::cout << "PASS: Division with small values calculations match." << std::endl;
        }
    }
    
    // Case 5: Complex conjugate division - Most likely source of bugs
    {
        std::cout << "\nTest Case 5: Division using conjugate formula check" << std::endl;
        Complex a(7.0, 8.0);
        Complex b(3.0, 4.0);
        
        printComplex(a, "a");
        printComplex(b, "b");
        
        // Manual calculation using the conjugate formula
        // (a+bi)/(c+di) = (a+bi)(c-di)/(c²+d²)
        double denominator = b.real() * b.real() + b.imag() * b.imag();
        double real_part = (a.real() * b.real() + a.imag() * b.imag()) / denominator;
        double imag_part = (a.imag() * b.real() - a.real() * b.imag()) / denominator;
        Complex expected(real_part, imag_part);
        
        // Direct division using the operator
        Complex result = a / b;
        
        printComplex(result, "a / b (using operator/)");
        printComplex(expected, "a / b (conjugate formula)");
        
        std::cout << "Checking calculation details:" << std::endl;
        std::cout << "Denominator: " << denominator << std::endl;
        std::cout << "Numerator real part: " << (a.real() * b.real() + a.imag() * b.imag()) << std::endl;
        std::cout << "Numerator imag part: " << (a.imag() * b.real() - a.real() * b.imag()) << std::endl;
        
        // Checking for sign errors in the imaginary part - a common bug!
        if (!approxEqual(result.real(), expected.real())) {
            std::cout << "ERROR: Real part of division is incorrect!" << std::endl;
        } else {
            std::cout << "PASS: Real part of division is correct." << std::endl;
        }
        
        if (!approxEqual(result.imag(), expected.imag())) {
            std::cout << "ERROR: Imaginary part of division is incorrect!" << std::endl;
            std::cout << "This is often due to a sign error in the formula implementation." << std::endl;
        } else {
            std::cout << "PASS: Imaginary part of division is correct." << std::endl;
        }
    }
    
    return 0;
}