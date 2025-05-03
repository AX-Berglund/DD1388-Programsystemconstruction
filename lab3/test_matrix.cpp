#include "Matrix.h"
#include <iostream>
#include <cassert>
#include <string>

// Helper function to print test results
void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

// Test basic constructors and getters
void testConstructors() {
    std::cout << "\n=== Testing Constructors ===\n";
    
    // Default constructor
    Matrix<int> m1;
    printTestResult("Default Constructor", m1.rows() == 0 && m1.cols() == 0);
    
    // Square matrix constructor
    Matrix<int> m2(3);
    printTestResult("Square Constructor", m2.rows() == 3 && m2.cols() == 3);
    
    // Rectangular matrix constructor
    Matrix<int> m3(2, 4);
    printTestResult("Rectangular Constructor", m3.rows() == 2 && m3.cols() == 4);
    
    // Initializer list constructor
    Matrix<int> m4 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printTestResult("Initializer List Constructor", m4.rows() == 3 && m4.cols() == 3);
    
    // Check initializer list values
    bool initListValuesCorrect = true;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (m4(i, j) != (i * 3 + j + 1)) {
                initListValuesCorrect = false;
                break;
            }
        }
    }
    printTestResult("Initializer List Values", initListValuesCorrect);
}

// Test copy and move constructors and assignment operators
void testCopyAndMove() {
    std::cout << "\n=== Testing Copy and Move Operations ===\n";
    
    // Copy constructor
    Matrix<int> m1(2, 2);
    m1(0, 0) = 1; m1(0, 1) = 2;
    m1(1, 0) = 3; m1(1, 1) = 4;
    
    Matrix<int> m2 = m1; // Copy constructor
    bool copyConstructorWorks = true;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (m2(i, j) != m1(i, j)) {
                copyConstructorWorks = false;
                break;
            }
        }
    }
    printTestResult("Copy Constructor", copyConstructorWorks);
    
    // Copy assignment
    Matrix<int> m3(1, 1);
    m3 = m1; // Copy assignment
    bool copyAssignmentWorks = true;
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (m3(i, j) != m1(i, j)) {
                copyAssignmentWorks = false;
                break;
            }
        }
    }
    printTestResult("Copy Assignment", copyAssignmentWorks);
    
    // Move constructor
    Matrix<int> m4(std::move(m2));
    bool moveConstructorWorks = (m2.rows() == 0 && m2.cols() == 0); // m2 should be empty after move
    
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (m4(i, j) != m1(i, j)) {
                moveConstructorWorks = false;
                break;
            }
        }
    }
    printTestResult("Move Constructor", moveConstructorWorks);
    
    // Move assignment
    Matrix<int> m5(1, 1);
    m5 = std::move(m4);
    bool moveAssignmentWorks = (m4.rows() == 0 && m4.cols() == 0); // m4 should be empty after move
    
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (m5(i, j) != m1(i, j)) {
                moveAssignmentWorks = false;
                break;
            }
        }
    }
    printTestResult("Move Assignment", moveAssignmentWorks);
}

// Test matrix operations
void testOperations() {
    std::cout << "\n=== Testing Matrix Operations ===\n";
    
    // Element access
    Matrix<int> m1(2, 2);
    m1(0, 0) = 1; m1(0, 1) = 2;
    m1(1, 0) = 3; m1(1, 1) = 4;
    printTestResult("Element Access", m1(0, 0) == 1 && m1(0, 1) == 2 && m1(1, 0) == 3 && m1(1, 1) == 4);
    
    // Matrix addition
    Matrix<int> m2(2, 2);
    m2(0, 0) = 5; m2(0, 1) = 6;
    m2(1, 0) = 7; m2(1, 1) = 8;
    
    Matrix<int> m3 = m1 + m2;
    bool additionWorks = (m3(0, 0) == 6 && m3(0, 1) == 8 && m3(1, 0) == 10 && m3(1, 1) == 12);
    printTestResult("Matrix Addition", additionWorks);
    
    // Matrix subtraction
    Matrix<int> m4 = m2 - m1;
    bool subtractionWorks = (m4(0, 0) == 4 && m4(0, 1) == 4 && m4(1, 0) == 4 && m4(1, 1) == 4);
    printTestResult("Matrix Subtraction", subtractionWorks);
    
    // Matrix multiplication
    Matrix<int> m5(2, 3);
    m5(0, 0) = 1; m5(0, 1) = 2; m5(0, 2) = 3;
    m5(1, 0) = 4; m5(1, 1) = 5; m5(1, 2) = 6;
    
    Matrix<int> m6(3, 2);
    m6(0, 0) = 7; m6(0, 1) = 8;
    m6(1, 0) = 9; m6(1, 1) = 10;
    m6(2, 0) = 11; m6(2, 1) = 12;
    
    Matrix<int> m7 = m5 * m6;
    // m7 should be 2x2 with:
    // [1*7 + 2*9 + 3*11, 1*8 + 2*10 + 3*12]
    // [4*7 + 5*9 + 6*11, 4*8 + 5*10 + 6*12]
    // = [58, 64, 139, 154]
    bool multiplicationWorks = (m7(0, 0) == 58 && m7(0, 1) == 64 && m7(1, 0) == 139 && m7(1, 1) == 154);
    printTestResult("Matrix Multiplication", multiplicationWorks);
    
    // Matrix compound assignment
    Matrix<int> m8 = m1;
    m8 += m2;
    bool compoundAdditionWorks = (m8(0, 0) == 6 && m8(0, 1) == 8 && m8(1, 0) == 10 && m8(1, 1) == 12);
    printTestResult("Compound Addition", compoundAdditionWorks);
    
    Matrix<int> m9 = m2;
    m9 -= m1;
    bool compoundSubtractionWorks = (m9(0, 0) == 4 && m9(0, 1) == 4 && m9(1, 0) == 4 && m9(1, 1) == 4);
    printTestResult("Compound Subtraction", compoundSubtractionWorks);
    
    Matrix<int> m10 = m5; // 2x3
    m10 *= m6; // 3x2
    bool compoundMultiplicationWorks = (m10(0, 0) == 58 && m10(0, 1) == 64 && m10(1, 0) == 139 && m10(1, 1) == 154);
    printTestResult("Compound Multiplication", compoundMultiplicationWorks);
}
// Extended test for reset method
void testResetMethod() {
    std::cout << "\n=== Extended Reset Method Test ===\n";
    
    // Test with integers
    {
        Matrix<int> m(2, 2);
        m(0, 0) = 1; m(0, 1) = 2;
        m(1, 0) = 3; m(1, 1) = 4;
        m.reset();
        
        // Check each element
        std::cout << "After reset, matrix contains: " << std::endl;
        for (size_t i = 0; i < m.rows(); i++) {
            for (size_t j = 0; j < m.cols(); j++) {
                std::cout << "m(" << i << "," << j << ") = " << m(i, j) << std::endl;
            }
        }
        
        bool allZeros = true;
        for (size_t i = 0; i < m.rows(); i++) {
            for (size_t j = 0; j < m.cols(); j++) {
                if (m(i, j) != 0) {
                    allZeros = false;
                    break;
                }
            }
        }
        printTestResult("Reset Integer Matrix", allZeros);
    }
    
    // Test with double
    {
        Matrix<double> m(2, 2);
        m(0, 0) = 1.1; m(0, 1) = 2.2;
        m(1, 0) = 3.3; m(1, 1) = 4.4;
        m.reset();
        
        bool allZeros = true;
        for (size_t i = 0; i < m.rows(); i++) {
            for (size_t j = 0; j < m.cols(); j++) {
                if (m(i, j) != 0.0) {
                    allZeros = false;
                    break;
                }
            }
        }
        printTestResult("Reset Double Matrix", allZeros);
    }
    
    // Test with custom class
    {
        class TestClass {
        public:
            TestClass() : value(0) {}
            bool operator==(const TestClass& other) const {
                return value == other.value;
            }
            int value;
        };
        
        Matrix<TestClass> m(2, 2);
        for (size_t i = 0; i < m.rows(); i++) {
            for (size_t j = 0; j < m.cols(); j++) {
                m(i, j).value = (i+1)*(j+1);
            }
        }
        m.reset();
        
        bool allDefault = true;
        for (size_t i = 0; i < m.rows(); i++) {
            for (size_t j = 0; j < m.cols(); j++) {
                if (m(i, j).value != 0) {
                    allDefault = false;
                    break;
                }
            }
        }
        printTestResult("Reset Custom Class Matrix", allDefault);
    }
    
    // Test edge cases
    {
        // Empty matrix
        Matrix<int> emptyMatrix;
        emptyMatrix.reset();
        printTestResult("Reset Empty Matrix", true); // Should not crash
        
        // 0x0 matrix
        Matrix<int> zeroMatrix(0, 0);
        zeroMatrix.reset();
        printTestResult("Reset 0x0 Matrix", true); // Should not crash
    }
}

// Extended comprehensive test for reset method
void testResetMethodExtended() {
    std::cout << "\n=== Extended Reset Method Test ===\n";
    
    // Test matrices of different dimensions
    std::vector<std::pair<size_t, size_t>> dimensions = {
        {1, 1},    // Single element
        {3, 3},    // Small square
        {5, 5},    // Medium square
        {1, 5},    // Row vector
        {5, 1},    // Column vector
        {2, 7},    // Wide rectangle
        {7, 2},    // Tall rectangle
        {10, 10}   // Larger matrix
    };
    
    // Test with int type
    std::cout << "Testing integer matrices:" << std::endl;
    for (const auto& dim : dimensions) {
        size_t rows = dim.first;
        size_t cols = dim.second;
        
        Matrix<int> m(rows, cols);
        
        // Fill with non-zero values
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                m(i, j) = (i+1) * (j+1);
            }
        }
        
        // Print a sample of values before reset
        std::cout << "Matrix " << rows << "x" << cols << " before reset (sample): ";
        if (rows > 0 && cols > 0) {
            std::cout << m(0, 0) << " ";
        }
        if (rows > 1 && cols > 1) {
            std::cout << m(1, 1) << " ";
        }
        std::cout << std::endl;
        
        // Reset the matrix
        m.reset();
        
        // Check if all elements are reset to 0
        bool allZeros = true;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (m(i, j) != 0) {
                    allZeros = false;
                    std::cout << "  Failed at position (" << i << "," << j << ") = " << m(i, j) << std::endl;
                    break;
                }
            }
            if (!allZeros) break;
        }
        
        // Print a sample of values after reset
        std::cout << "Matrix " << rows << "x" << cols << " after reset (sample): ";
        if (rows > 0 && cols > 0) {
            std::cout << m(0, 0) << " ";
        }
        if (rows > 1 && cols > 1) {
            std::cout << m(1, 1) << " ";
        }
        std::cout << std::endl;
        
        printTestResult("Reset " + std::to_string(rows) + "x" + std::to_string(cols) + " Integer Matrix", allZeros);
    }
    
    // Test with double type (a few dimensions)
    std::cout << "\nTesting double matrices:" << std::endl;
    for (const auto& dim : {std::make_pair(2, 2), std::make_pair(3, 4)}) {
        size_t rows = dim.first;
        size_t cols = dim.second;
        
        Matrix<double> m(rows, cols);
        
        // Fill with non-zero values
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                m(i, j) = 1.1 * (i+1) * (j+1);
            }
        }
        
        // Reset the matrix
        m.reset();
        
        // Check if all elements are reset to 0.0
        bool allZeros = true;
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (m(i, j) != 0.0) {
                    allZeros = false;
                    std::cout << "  Failed at position (" << i << "," << j << ") = " << m(i, j) << std::endl;
                    break;
                }
            }
            if (!allZeros) break;
        }
        
        printTestResult("Reset " + std::to_string(rows) + "x" + std::to_string(cols) + " Double Matrix", allZeros);
    }
    
    // Test with custom class
    std::cout << "\nTesting custom class matrices:" << std::endl;
    {
        class TestClass {
        public:
            TestClass() : value(0) {}
            TestClass(int v) : value(v) {}
            bool operator==(const TestClass& other) const {
                return value == other.value;
            }
            bool operator!=(const TestClass& other) const {
                return value != other.value;
            }
            int value;
        };
        
        Matrix<TestClass> m(3, 3);
        
        // Fill with non-default values
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                m(i, j).value = 10;
            }
        }
        
        // Reset the matrix
        m.reset();
        
        // Check if all elements are reset to default
        bool allDefault = true;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (m(i, j).value != 0) {
                    allDefault = false;
                    std::cout << "  Failed at position (" << i << "," << j << ") = " << m(i, j).value << std::endl;
                    break;
                }
            }
            if (!allDefault) break;
        }
        
        printTestResult("Reset Custom Class Matrix", allDefault);
    }
    
    // Test resetting an already-reset matrix
    std::cout << "\nTesting double-reset:" << std::endl;
    {
        Matrix<int> m(3, 3);
        
        // Reset once
        m.reset();
        
        // Fill with non-zero values
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                m(i, j) = 5;
            }
        }
        
        // Reset again
        m.reset();
        
        // Check if all elements are reset to 0
        bool allZeros = true;
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                if (m(i, j) != 0) {
                    allZeros = false;
                    break;
                }
            }
            if (!allZeros) break;
        }
        
        printTestResult("Double Reset Test", allZeros);
    }
    
    // Test edge cases
    std::cout << "\nTesting edge cases:" << std::endl;
    {
        // Empty matrix
        Matrix<int> emptyMatrix;
        emptyMatrix.reset();
        printTestResult("Reset Empty Matrix", true); // Should not crash
        
        // 0x0 matrix
        Matrix<int> zeroMatrix(0, 0);
        zeroMatrix.reset();
        printTestResult("Reset 0x0 Matrix", true); // Should not crash
    }
}

// Test matrix modification methods
void testModifications() {
    std::cout << "\n=== Testing Matrix Modifications ===\n";
    
    // Reset
    Matrix<int> m1(2, 2);
    m1(0, 0) = 1; m1(0, 1) = 2;
    m1(1, 0) = 3; m1(1, 1) = 4;
    m1.reset();
    bool resetWorks = (m1(0, 0) == 0 && m1(0, 1) == 0 && m1(1, 0) == 0 && m1(1, 1) == 0);
    printTestResult("Reset", resetWorks);
    
    // Insert row
    Matrix<int> m2(2, 2);
    m2(0, 0) = 1; m2(0, 1) = 2;
    m2(1, 0) = 3; m2(1, 1) = 4;
    m2.insert_row(1);
    
    bool insertRowWorks = (m2.rows() == 3 && m2.cols() == 2 &&
                          m2(0, 0) == 1 && m2(0, 1) == 2 &&
                          m2(1, 0) == 0 && m2(1, 1) == 0 &&
                          m2(2, 0) == 3 && m2(2, 1) == 4);
    printTestResult("Insert Row", insertRowWorks);
    
    // Append row
    Matrix<int> m3(2, 2);
    m3(0, 0) = 1; m3(0, 1) = 2;
    m3(1, 0) = 3; m3(1, 1) = 4;
    m3.append_row(0);
    
    bool appendRowWorks = (m3.rows() == 3 && m3.cols() == 2 &&
                          m3(0, 0) == 1 && m3(0, 1) == 2 &&
                          m3(1, 0) == 0 && m3(1, 1) == 0 &&
                          m3(2, 0) == 3 && m3(2, 1) == 4);
    printTestResult("Append Row", appendRowWorks);
    
    // Remove row
    Matrix<int> m4(3, 2);
    m4(0, 0) = 1; m4(0, 1) = 2;
    m4(1, 0) = 3; m4(1, 1) = 4;
    m4(2, 0) = 5; m4(2, 1) = 6;
    m4.remove_row(1);
    
    bool removeRowWorks = (m4.rows() == 2 && m4.cols() == 2 &&
                          m4(0, 0) == 1 && m4(0, 1) == 2 &&
                          m4(1, 0) == 5 && m4(1, 1) == 6);
    printTestResult("Remove Row", removeRowWorks);
    
    // Insert column
    Matrix<int> m5(2, 2);
    m5(0, 0) = 1; m5(0, 1) = 2;
    m5(1, 0) = 3; m5(1, 1) = 4;
    m5.insert_column(1);
    
    bool insertColumnWorks = (m5.rows() == 2 && m5.cols() == 3 &&
                            m5(0, 0) == 1 && m5(0, 1) == 0 && m5(0, 2) == 2 &&
                            m5(1, 0) == 3 && m5(1, 1) == 0 && m5(1, 2) == 4);
    printTestResult("Insert Column", insertColumnWorks);
    
    // Append column
    Matrix<int> m6(2, 2);
    m6(0, 0) = 1; m6(0, 1) = 2;
    m6(1, 0) = 3; m6(1, 1) = 4;
    m6.append_column(0);
    
    bool appendColumnWorks = (m6.rows() == 2 && m6.cols() == 3 &&
                            m6(0, 0) == 1 && m6(0, 1) == 0 && m6(0, 2) == 2 &&
                            m6(1, 0) == 3 && m6(1, 1) == 0 && m6(1, 2) == 4);
    printTestResult("Append Column", appendColumnWorks);
    
    // Remove column
    Matrix<int> m7(2, 3);
    m7(0, 0) = 1; m7(0, 1) = 2; m7(0, 2) = 3;
    m7(1, 0) = 4; m7(1, 1) = 5; m7(1, 2) = 6;
    m7.remove_column(1);
    
    bool removeColumnWorks = (m7.rows() == 2 && m7.cols() == 2 &&
                            m7(0, 0) == 1 && m7(0, 1) == 3 &&
                            m7(1, 0) == 4 && m7(1, 1) == 6);
    printTestResult("Remove Column", removeColumnWorks);
}

// Test identity matrix function
void testIdentity() {
    std::cout << "\n=== Testing Identity Matrix ===\n";
    
    Matrix<int> identity_matrix = identity<int>(3);
    bool identityWorks = (identity_matrix.rows() == 3 && identity_matrix.cols() == 3 &&
                         identity_matrix(0, 0) == 1 && identity_matrix(0, 1) == 0 && identity_matrix(0, 2) == 0 &&
                         identity_matrix(1, 0) == 0 && identity_matrix(1, 1) == 1 && identity_matrix(1, 2) == 0 &&
                         identity_matrix(2, 0) == 0 && identity_matrix(2, 1) == 0 && identity_matrix(2, 2) == 1);
    printTestResult("Identity Matrix", identityWorks);
}

// Test iterators
void testIterators() {
    std::cout << "\n=== Testing Iterators ===\n";
    
    Matrix<int> m1 = {1, 2, 3, 4};
    int sum = 0;
    for (auto it = m1.begin(); it != m1.end(); ++it) {
        sum += *it;
    }
    printTestResult("Matrix Iterators", sum == 10); // 1+2+3+4 = 10
}

// Test exception handling
void testExceptions() {
    std::cout << "\n=== Testing Exception Handling ===\n";
    
    // Test out of bounds access
    Matrix<int> m1(2, 2);
    bool exceptionThrown = false;
    try {
        m1(2, 1) = 10; // Should throw exception
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    printTestResult("Out of Bounds Exception", exceptionThrown);
    
    // Test invalid matrix multiplication
    Matrix<int> m2(2, 3);
    Matrix<int> m3(4, 2);
    exceptionThrown = false;
    try {
        Matrix<int> m4 = m2 * m3; // Should throw exception (dimensions don't match)
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    printTestResult("Invalid Multiplication Exception", exceptionThrown);
    
    // Test invalid row/column operations
    Matrix<int> m5(3, 3);
    exceptionThrown = false;
    try {
        m5.insert_row(4); // Should throw exception (row index out of range)
    } catch (const std::out_of_range&) {
        exceptionThrown = true;
    }
    printTestResult("Invalid Row Operation Exception", exceptionThrown);
}


// Add this to your main function
int main() {
    std::cout << "=== Matrix Class Test Suite ===" << std::endl;
    
    testConstructors();
    testCopyAndMove();
    testOperations();
    testModifications();
    testResetMethod();
    testIdentity();
    testIterators();
    testExceptions();
    
    // Add the new extended test
    testResetMethodExtended();
    
    std::cout << "\n=== Test Summary ===" << std::endl;
    std::cout << "All tests completed. Check results above for failures." << std::endl;
    
    return 0;
}
