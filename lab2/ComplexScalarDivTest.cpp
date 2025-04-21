#include <iostream>
#include <iomanip>
#include <cmath>
#include "Complex.h"

// Helper function for comparing doubles with tolerance
bool approxEqual(double a, double b, double epsilon = 1e-10) {
    return std::abs(a - b) < epsilon;
}

int main() {
    std::cout << "SCALAR DIVISION BY COMPLEX NUMBER TEST" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    // Set high precision for outputs
    std::cout << std::fixed << std::setprecision(15);
    
    // Test cases for scalar / complex
    std::cout << "\nTesting scalar / complex:" << std::endl;
    std::cout << "---------------------------" << std::endl;
    
    struct TestCase {
        double scalar;
        double re;
        double im;
        std::string description;
    };
    
    TestCase tests[] = {
        {10.0, 2.0, 3.0, "Standard case"},
        {1.0, 0.0, 1.0, "Pure imaginary denominator"},
        {5.0, 5.0, 0.0, "Pure real denominator"},
        {2.0, 1e-10, 1e-10, "Very small denominator"},
        {-3.0, 2.0, -4.0, "Negative scalar with mixed sign complex"},
        {0.0, 3.0, 4.0, "Zero scalar"},
        {1e10, 2.0, 3.0, "Very large scalar"},
        {1e-10, 2.0, 3.0, "Very small scalar"}
    };
    
    int failures = 0;
    
    for (const auto& test : tests) {
        std::cout << "\nCase: " << test.description << std::endl;
        double scalar = test.scalar;
        Complex c(test.re, test.im);
        
        std::cout << "scalar = " << scalar << std::endl;
        std::cout << "complex = (" << c.real() << ", " << c.imag() << ")" << std::endl;
        
        // Manual calculation for reference
        double denominator = c.real() * c.real() + c.imag() * c.imag();
        Complex expected(
            scalar * c.real() / denominator,
            -scalar * c.imag() / denominator  // Note the negative sign here!
        );
        
        // Using the operator
        Complex result = scalar / c;
        
        std::cout << "Expected result: (" << expected.real() << ", " << expected.imag() << ")" << std::endl;
        std::cout << "Actual result:   (" << result.real() << ", " << result.imag() << ")" << std::endl;
        
        bool correct = approxEqual(result.real(), expected.real()) && 
                      approxEqual(result.imag(), expected.imag());
                      
        if (!correct) {
            std::cout << "FAILED: Results don't match!" << std::endl;
            std::cout << "Difference: real = " << result.real() - expected.real() 
                      << ", imag = " << result.imag() - expected.imag() << std::endl;
            
            // Check if the error is in the sign of the imaginary part (common mistake)
            if (approxEqual(result.real(), expected.real()) && 
                approxEqual(result.imag(), -expected.imag())) {
                std::cout << "ERROR DETECTED: Imaginary part has the wrong sign!" << std::endl;
                std::cout << "This is a common error in the implementation of scalar / complex." << std::endl;
                std::cout << "Remember: scalar / complex = scalar * conjugate(complex) / |complex|²" << std::endl;
            }
            
            failures++;
        } else {
            std::cout << "PASSED: Results match correctly." << std::endl;
        }
        
        // Additional verification: (scalar/c) * c should approximately equal scalar
        Complex verification = result * c;
        std::cout << "Verification (scalar/c)*c = (" << verification.real() << ", " 
                  << verification.imag() << ")" << std::endl;
        
        if (!approxEqual(verification.real(), scalar) || !approxEqual(verification.imag(), 0.0)) {
            std::cout << "VERIFICATION FAILED: (scalar/c)*c != scalar" << std::endl;
            failures++;
        } else {
            std::cout << "Verification passed: (scalar/c)*c = scalar" << std::endl;
        }
    }
    
    std::cout << "\n==================================" << std::endl;
    if (failures == 0) {
        std::cout << "All scalar division by complex tests PASSED!" << std::endl;
    } else {
        std::cout << failures << " test cases FAILED!" << std::endl;
        std::cout << "Common source of error: Check the implementation of operator/(double, const Complex&)" << std::endl;
        std::cout << "Make sure the formula is correctly implemented:" << std::endl;
        std::cout << "scalar / complex = (scalar * complex.real / |complex|², -scalar * complex.imag / |complex|²)" << std::endl;
        std::cout << "Note the NEGATIVE sign in the imaginary part!" << std::endl;
    }
    
    return failures;
}