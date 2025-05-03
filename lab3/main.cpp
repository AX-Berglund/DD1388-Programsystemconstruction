#include "Matrix.h"
#include <iostream>
#include <string>

void printSectionHeader(const std::string& title) {
    std::cout << "\n====== " << title << " ======\n";
}

// Basic constructor tests
void testMatrixConstructors() {
    printSectionHeader("Testing Matrix Constructors");
    
    std::cout << "Default constructor:\n";
    Matrix<int> m1;
    std::cout << m1 << std::endl;
    
    std::cout << "Square matrix constructor (0x0):\n";
    Matrix<int> m2(0);
    std::cout << m2 << std::endl;
    
    std::cout << "Square matrix constructor (4x4):\n";
    Matrix<int> m3(4);
    std::cout << m3 << std::endl;
    
    std::cout << "Rectangular matrix constructor (4x3):\n";
    Matrix<int> m4(4, 3);
    std::cout << m4 << std::endl;
    
    std::cout << "Initializer list constructor:\n";
    Matrix<int> m5 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << m5 << std::endl;
}

// Test copy and move operations
void testCopyAndMove() {
    printSectionHeader("Testing Copy and Move Operations");
    
    // Create a test matrix
    Matrix<int> m1(2, 2);
    m1(0, 0) = 1; m1(0, 1) = 2;
    m1(1, 0) = 3; m1(1, 1) = 4;
    std::cout << "Original matrix m1:\n" << m1 << std::endl;
    
    // Test copy constructor
    std::cout << "Copy constructor test:\n";
    Matrix<int> m2 = m1;
    std::cout << "Copy (m2):\n" << m2 << std::endl;
    std::cout << "Original (m1) after copy:\n" << m1 << std::endl;
    
    // Test move constructor
    std::cout << "Move constructor test:\n";
    Matrix<int> m3 = std::move(m2);
    std::cout << "Moved-to (m3):\n" << m3 << std::endl;
    std::cout << "Moved-from (m2) after move:\n" << m2 << std::endl;
    
    // Test copy assignment
    Matrix<int> m4(1, 1);
    std::cout << "Before copy assignment (m4):\n" << m4 << std::endl;
    m4 = m1;
    std::cout << "After copy assignment (m4):\n" << m4 << std::endl;
    std::cout << "Original (m1) after copy assignment:\n" << m1 << std::endl;
    
    // Test move assignment
    Matrix<int> m5(1, 1);
    std::cout << "Before move assignment (m5):\n" << m5 << std::endl;
    m5 = std::move(m3);
    std::cout << "After move assignment (m5):\n" << m5 << std::endl;
    std::cout << "Moved-from (m3) after move assignment:\n" << m3 << std::endl;
}

// Test basic accessors
void testAccessors() {
    printSectionHeader("Testing Accessors");
    
    Matrix<int> m(3, 4);
    std::cout << "Matrix dimensions: " << m.rows() << " rows × " << m.cols() << " columns" << std::endl;
    
    // Test element access
    Matrix<int> m2(2, 2);
    m2(0, 0) = 10; m2(0, 1) = 20;
    m2(1, 0) = 30; m2(1, 1) = 40;
    std::cout << "Element access test:\n";
    std::cout << "m2(0,0) = " << m2(0, 0) << std::endl;
    std::cout << "m2(0,1) = " << m2(0, 1) << std::endl;
    std::cout << "m2(1,0) = " << m2(1, 0) << std::endl;
    std::cout << "m2(1,1) = " << m2(1, 1) << std::endl;
}

// Test matrix arithmetic operations
void testMatrixOperations() {
    printSectionHeader("Testing Matrix Operations");
    
    // Create test matrices
    Matrix<int> m1(2, 2);
    m1(0, 0) = 1; m1(0, 1) = 2;
    m1(1, 0) = 3; m1(1, 1) = 4;
    
    Matrix<int> m2(2, 2);
    m2(0, 0) = 5; m2(0, 1) = 6;
    m2(1, 0) = 7; m2(1, 1) = 8;
    
    std::cout << "Matrix m1:\n" << m1 << std::endl;
    std::cout << "Matrix m2:\n" << m2 << std::endl;
    
    // Test multiplication
    std::cout << "Multiplication (m1 * m2):\n";
    Matrix<int> mult_result = m1 * m2;
    std::cout << mult_result << std::endl;
    
    // Test addition
    std::cout << "Addition (m1 + m2):\n";
    Matrix<int> add_result = m1 + m2;
    std::cout << add_result << std::endl;
    
    // Test subtraction
    std::cout << "Subtraction (m1 - m2):\n";
    Matrix<int> sub_result = m1 - m2;
    std::cout << sub_result << std::endl;
    
    // Test compound operators
    Matrix<int> m3 = m1;
    std::cout << "Testing m3 *= m2 (before):\n" << m3 << std::endl;
    m3 *= m2;
    std::cout << "After m3 *= m2:\n" << m3 << std::endl;
    
    Matrix<int> m4 = m1;
    std::cout << "Testing m4 += m2 (before):\n" << m4 << std::endl;
    m4 += m2;
    std::cout << "After m4 += m2:\n" << m4 << std::endl;
    
    Matrix<int> m5 = m1;
    std::cout << "Testing m5 -= m2 (before):\n" << m5 << std::endl;
    m5 -= m2;
    std::cout << "After m5 -= m2:\n" << m5 << std::endl;
}

// Test matrix modification methods
void testMatrixModifications() {
    printSectionHeader("Testing Matrix Modifications");
    
    // Create a test matrix
    Matrix<int> m(3, 3);
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            m(i, j) = i * 3 + j + 1;
        }
    }
    std::cout << "Original matrix:\n" << m << std::endl;
    
    // Test reset
    Matrix<int> m_reset = m;
    std::cout << "Testing reset (before):\n" << m_reset << std::endl;
    m_reset.reset();
    std::cout << "After reset:\n" << m_reset << std::endl;
    
    // Test insert_row
    Matrix<int> m_insert_row = m;
    std::cout << "Testing insert_row at position 1 (before):\n" << m_insert_row << std::endl;
    m_insert_row.insert_row(1);
    std::cout << "After insert_row(1):\n" << m_insert_row << std::endl;
    
    // Test append_row
    Matrix<int> m_append_row = m;
    std::cout << "Testing append_row at position 1 (before):\n" << m_append_row << std::endl;
    m_append_row.append_row(1);
    std::cout << "After append_row(1):\n" << m_append_row << std::endl;
    
    // Test remove_row
    Matrix<int> m_remove_row = m;
    std::cout << "Testing remove_row at position 1 (before):\n" << m_remove_row << std::endl;
    m_remove_row.remove_row(1);
    std::cout << "After remove_row(1):\n" << m_remove_row << std::endl;
    
    // Test insert_column
    Matrix<int> m_insert_col = m;
    std::cout << "Testing insert_column at position 1 (before):\n" << m_insert_col << std::endl;
    m_insert_col.insert_column(1);
    std::cout << "After insert_column(1):\n" << m_insert_col << std::endl;
    
    // Test append_column
    Matrix<int> m_append_col = m;
    std::cout << "Testing append_column at position 1 (before):\n" << m_append_col << std::endl;
    m_append_col.append_column(1);
    std::cout << "After append_column(1):\n" << m_append_col << std::endl;
    
    // Test remove_column
    Matrix<int> m_remove_col = m;
    std::cout << "Testing remove_column at position 1 (before):\n" << m_remove_col << std::endl;
    m_remove_col.remove_column(1);
    std::cout << "After remove_column(1):\n" << m_remove_col << std::endl;
}

// Test identity matrix function
void testIdentityMatrix() {
    printSectionHeader("Testing Identity Matrix");
    
    for (size_t dim = 2; dim <= 5; dim++) {
        std::cout << "Identity matrix of dimension " << dim << ":\n";
        Matrix<int> id = identity<int>(dim);
        std::cout << id << std::endl;
    }
}

// Test iterators
void testIterators() {
    printSectionHeader("Testing Iterators");
    
    Matrix<int> m = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Matrix:\n" << m << std::endl;
    
    std::cout << "Elements using iterators: ";
    for (auto it = m.begin(); it != m.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Calculate sum using iterators
    int sum = 0;
    for (auto it = m.begin(); it != m.end(); ++it) {
        sum += *it;
    }
    std::cout << "Sum of all elements: " << sum << std::endl;
}

int main() {
    std::cout << "=== Matrix Class Testing Program ===\n";
    
    // Run tests
    testMatrixConstructors();
    testCopyAndMove();
    testAccessors();
    testMatrixOperations();
    testMatrixModifications();
    testIdentityMatrix();
    testIterators();
    
    std::cout << "\n=== Testing Complete ===\n";
    return 0;
}