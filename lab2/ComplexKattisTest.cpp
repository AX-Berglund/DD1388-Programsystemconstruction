#include <iostream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include "Complex.h"

// Helper function for comparing doubles with tolerance
bool approxEqual(double a, double b, double epsilon = 1e-10) {
    return std::abs(a - b) < epsilon;
}

// Helper function for comparing complex numbers with tolerance
bool approxEqual(const Complex& a, const Complex& b, double epsilon = 1e-10) {
    return approxEqual(a.real(), b.real(), epsilon) && 
           approxEqual(a.imag(), b.imag(), epsilon);
}

// Helper to print complex numbers with detailed info
void printComplex(const Complex& c, const std::string& label) {
    std::cout << label << ": (" << c.real() << ", " << c.imag() << ")" << std::endl;
}

// Test helper function to track failures
#define TEST(condition, message) \
    if (!(condition)) { \
        std::cout << "FAILED: " << message << " at line " << __LINE__ << std::endl; \
        failCount++; \
    } else { \
        std::cout << "PASSED: " << message << std::endl; \
    }

int main() {
    int failCount = 0;
    std::cout << std::fixed << std::setprecision(10);
    
    std::cout << "========= CONSTRUCTION =========" << std::endl;
    {
        Complex c1;
        TEST(c1.real() == 0.0 && c1.imag() == 0.0, "Default constructor");
        
        Complex c2(3.5);
        TEST(c2.real() == 3.5 && c2.imag() == 0.0, "Real-only constructor");
        
        Complex c3(2.5, 3.5);
        TEST(c3.real() == 2.5 && c3.imag() == 3.5, "Real and imaginary constructor");
        
        Complex c4(c3);
        TEST(c4.real() == c3.real() && c4.imag() == c3.imag(), "Copy constructor");
    }
    
    std::cout << "\n========= ASSIGNMENT =========" << std::endl;
    {
        Complex c1(2.5, 3.5);
        Complex c2;
        c2 = c1;
        TEST(c2.real() == 2.5 && c2.imag() == 3.5, "Assignment operator");
        
        // Self-assignment (this tests for memory issues)
        Complex c3(1.5, 2.5);
        c3 = c3;
        TEST(c3.real() == 1.5 && c3.imag() == 2.5, "Self-assignment");
    }
    
    std::cout << "\n========= ARITHMETIC ASSIGNMENTS =========" << std::endl;
    {
        // Testing +=
        Complex c1(2.0, 3.0);
        Complex c2(4.0, 5.0);
        Complex c3 = c1;
        
        c3 += c2;
        TEST(approxEqual(c3.real(), 6.0) && approxEqual(c3.imag(), 8.0), "Complex += Complex");
        
        c3 = c1;
        c3 += 2.5;
        TEST(approxEqual(c3.real(), 4.5) && approxEqual(c3.imag(), 3.0), "Complex += scalar");
        
        // Testing -=
        c3 = c1;
        c3 -= c2;
        TEST(approxEqual(c3.real(), -2.0) && approxEqual(c3.imag(), -2.0), "Complex -= Complex");
        
        c3 = c1;
        c3 -= 1.5;
        TEST(approxEqual(c3.real(), 0.5) && approxEqual(c3.imag(), 3.0), "Complex -= scalar");
        
        // Testing *=
        c3 = c1;
        c3 *= c2;
        // (2 + 3i) * (4 + 5i) = 8 + 10i + 12i + 15i² = 8 + 22i - 15 = -7 + 22i
        TEST(approxEqual(c3.real(), -7.0) && approxEqual(c3.imag(), 22.0), "Complex *= Complex");
        
        c3 = c1;
        c3 *= 2.0;
        TEST(approxEqual(c3.real(), 4.0) && approxEqual(c3.imag(), 6.0), "Complex *= scalar");
        
        // Testing /=
        c1 = Complex(8.0, 16.0);
        c2 = Complex(2.0, 4.0);
        c3 = c1;
        c3 /= c2;
        
        // Manual calculation for division
        double denominator = c2.real() * c2.real() + c2.imag() * c2.imag();
        double expectedReal = (c1.real() * c2.real() + c1.imag() * c2.imag()) / denominator;
        double expectedImag = (c1.imag() * c2.real() - c1.real() * c2.imag()) / denominator;
        
        TEST(approxEqual(c3.real(), expectedReal) && approxEqual(c3.imag(), expectedImag), 
             "Complex /= Complex");
        
        // For this specific case, we expect c3 to be (4, 0)
        TEST(approxEqual(c3.real(), 4.0) && approxEqual(c3.imag(), 0.0), 
             "Complex /= Complex specific case");
        
        c3 = c1;
        c3 /= 2.0;
        TEST(approxEqual(c3.real(), 4.0) && approxEqual(c3.imag(), 8.0), "Complex /= scalar");
    }
    
    std::cout << "\n========= BOOLEAN OPERATORS =========" << std::endl;
    {
        Complex c1(2.0, 3.0);
        Complex c2(2.0, 3.0);
        Complex c3(3.0, 4.0);
        
        TEST(c1 == c2, "operator== (true case)");
        TEST(!(c1 == c3), "operator== (false case)");
        TEST(c1 != c3, "operator!= (true case)");
        TEST(!(c1 != c2), "operator!= (false case)");
        
        // Testing < operator (comparing absolutes)
        TEST(c1 < c3, "operator< (true case, |c1| < |c3|)");
        TEST(!(c3 < c1), "operator< (false case, |c3| > |c1|)");
        
        // Testing == and != with scalar
        Complex c4(5.0, 0.0);
        double scalar = 5.0;
        
        TEST(c4 == scalar, "Complex == scalar (true case)");
        TEST(!(c1 == scalar), "Complex == scalar (false case)");
        TEST(scalar == c4, "scalar == Complex (true case)");
        TEST(!(scalar == c1), "scalar == Complex (false case)");
        
        TEST(c1 != scalar, "Complex != scalar (true case)");
        TEST(!(c4 != scalar), "Complex != scalar (false case)");
        TEST(scalar != c1, "scalar != Complex (true case)");
        TEST(!(scalar != c4), "scalar != Complex (false case)");
    }
    
    std::cout << "\n========= ABSOLUTE VALUE =========" << std::endl;
    {
        Complex c1(3.0, 4.0);
        double absValue = abs(c1);
        TEST(approxEqual(absValue, 5.0), "abs() function");
        
        Complex c2(0.0, 0.0);
        absValue = abs(c2);
        TEST(approxEqual(absValue, 0.0), "abs() of zero");
        
        // Testing very large and very small values
        Complex c3(1e15, 1e15);
        absValue = abs(c3);
        double expected = 1e15 * std::sqrt(2.0);
        TEST(approxEqual(absValue, expected, 1e10), "abs() of very large values");
        
        Complex c4(1e-15, 1e-15);
        absValue = abs(c4);
        expected = 1e-15 * std::sqrt(2.0);
        TEST(approxEqual(absValue, expected, 1e-20), "abs() of very small values");
    }
    
    std::cout << "\n========= ARITHMETIC OPERATIONS =========" << std::endl;
    {
        Complex c1(2.0, 3.0);
        Complex c2(4.0, 5.0);
        
        // Complex + Complex
        Complex result = c1 + c2;
        TEST(approxEqual(result.real(), 6.0) && approxEqual(result.imag(), 8.0), "Complex + Complex");
        
        // Complex - Complex
        result = c1 - c2;
        TEST(approxEqual(result.real(), -2.0) && approxEqual(result.imag(), -2.0), "Complex - Complex");
        
        // Complex * Complex
        result = c1 * c2;
        TEST(approxEqual(result.real(), -7.0) && approxEqual(result.imag(), 22.0), "Complex * Complex");
        
        // Complex / Complex
        Complex c3(8.0, 16.0);
        Complex c4(2.0, 4.0);
        result = c3 / c4;
        TEST(approxEqual(result.real(), 4.0) && approxEqual(result.imag(), 0.0), "Complex / Complex");
        
        // Complex + scalar
        result = c1 + 3.0;
        TEST(approxEqual(result.real(), 5.0) && approxEqual(result.imag(), 3.0), "Complex + scalar");
        
        // scalar + Complex
        result = 3.0 + c1;
        TEST(approxEqual(result.real(), 5.0) && approxEqual(result.imag(), 3.0), "scalar + Complex");
        
        // Complex - scalar
        result = c1 - 1.0;
        TEST(approxEqual(result.real(), 1.0) && approxEqual(result.imag(), 3.0), "Complex - scalar");
        
        // scalar - Complex
        result = 5.0 - c1;
        TEST(approxEqual(result.real(), 3.0) && approxEqual(result.imag(), -3.0), "scalar - Complex");
        
        // Complex * scalar
        result = c1 * 2.0;
        TEST(approxEqual(result.real(), 4.0) && approxEqual(result.imag(), 6.0), "Complex * scalar");
        
        // scalar * Complex
        result = 2.0 * c1;
        TEST(approxEqual(result.real(), 4.0) && approxEqual(result.imag(), 6.0), "scalar * Complex");
        
        // Complex / scalar
        result = c1 / 2.0;
        TEST(approxEqual(result.real(), 1.0) && approxEqual(result.imag(), 1.5), "Complex / scalar");
        
        // scalar / Complex - POTENTIAL BUG AREA!
        result = 10.0 / c1;
        
        // Manual calculation for scalar / Complex
        double denominator = c1.real() * c1.real() + c1.imag() * c1.imag();
        double expectedReal = 10.0 * c1.real() / denominator;
        double expectedImag = -10.0 * c1.imag() / denominator;  // Note the negative sign
        
        std::cout << "scalar / Complex test:" << std::endl;
        std::cout << "  Expected: (" << expectedReal << ", " << expectedImag << ")" << std::endl;
        std::cout << "  Result:   (" << result.real() << ", " << result.imag() << ")" << std::endl;
        
        TEST(approxEqual(result.real(), expectedReal) && approxEqual(result.imag(), expectedImag), 
             "scalar / Complex");
    }
    
    std::cout << "\n========= LITERAL OPERATOR =========" << std::endl;
    {
        // Testing complex literal operators
        Complex c1 = 3.0_i;
        TEST(approxEqual(c1.real(), 0.0) && approxEqual(c1.imag(), 3.0), "operator\"\"_i(long double)");
        
        Complex c2 = 4_i;
        TEST(approxEqual(c2.real(), 0.0) && approxEqual(c2.imag(), 4.0), "operator\"\"_i(unsigned long long)");
        
        // Test combinations with literals
        Complex c3 = Complex(2.0, 0.0) + 3.0_i;
        TEST(approxEqual(c3.real(), 2.0) && approxEqual(c3.imag(), 3.0), "Complex + literal");
        
        Complex c4 = 2.0 * 3.0_i;
        TEST(approxEqual(c4.real(), 0.0) && approxEqual(c4.imag(), 6.0), "scalar * literal");
    }
    
    std::cout << "\n========= INPUT/OUTPUT =========" << std::endl;
    {
        // Testing output
        Complex c1(3.5, 4.5);
        std::ostringstream oss;
        oss << c1;
        TEST(oss.str() == "(3.5,4.5)", "operator<<");
        
        // Testing input with format (real,imaginary)
        std::istringstream iss1("(2.5,3.5)");
        Complex c2;
        iss1 >> c2;
        TEST(approxEqual(c2.real(), 2.5) && approxEqual(c2.imag(), 3.5), 
             "operator>> with (real,imaginary)");
        
        // Testing input with format (real)
        std::istringstream iss2("(4.5)");
        Complex c3;
        iss2 >> c3;
        TEST(approxEqual(c3.real(), 4.5) && approxEqual(c3.imag(), 0.0), 
             "operator>> with (real)");
        
        // Testing input with format real
        std::istringstream iss3("5.5");
        Complex c4;
        iss3 >> c4;
        TEST(approxEqual(c4.real(), 5.5) && approxEqual(c4.imag(), 0.0), 
             "operator>> with real");
        
        // Testing parsing with whitespace
        std::istringstream iss4("  (  6.5  ,  7.5  )  ");
        Complex c5;
        iss4 >> c5;
        TEST(approxEqual(c5.real(), 6.5) && approxEqual(c5.imag(), 7.5), 
             "operator>> with whitespace");
        
        // Testing whether stream state is properly set
        std::istringstream iss5("invalid");
        Complex c6;
        iss5 >> c6;
        TEST(iss5.fail(), "operator>> sets failbit for invalid input");
    }
    
    // Summary
    std::cout << "\n========= SUMMARY =========" << std::endl;
    if (failCount == 0) {
        std::cout << "All tests passed!" << std::endl;
    } else {
        std::cout << "Failed " << failCount << " tests." << std::endl;
    }
    
    return failCount;
}