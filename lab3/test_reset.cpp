#include "Matrix.h"
#include <cassert>
#include <iostream>
#include <string>
#include <complex>
#include <typeinfo>

// Helper function to print matrix state
template<typename T>
void print_matrix_state(const Matrix<T>& mat, const std::string& label) {
    std::cout << label << " (" << mat.rows() << "x" << mat.cols() << "):" << std::endl;
    std::cout << mat;
}

// Helper function to print detailed matrix info
template<typename T>
void print_detailed_matrix_state(const Matrix<T>& mat, const std::string& label) {
    std::cout << "\n=== " << label << " ===" << std::endl;
    std::cout << "Type: " << typeid(T).name() << std::endl;
    std::cout << "Dimensions: " << mat.rows() << "x" << mat.cols() << std::endl;
    std::cout << "Contents:" << std::endl;
    std::cout << mat;
    std::cout << "===================" << std::endl;
}

// Custom type to test default constructor behavior
class CustomType {
public:
    CustomType() : value(555) {}  // Default constructor sets to 42
    CustomType(int v) : value(v) {}
    bool operator==(const CustomType& other) const { return value == other.value; }
    bool operator!=(const CustomType& other) const { return !(*this == other); }
    friend std::ostream& operator<<(std::ostream& os, const CustomType& ct) {
        os << ct.value;
        return os;
    }
private:
    int value;
};

void test_reset_empty_matrix() {
    std::cout << "\nTesting reset on empty matrix..." << std::endl;
    Matrix<int> empty;
    print_matrix_state(empty, "Before reset");
    empty.reset();
    print_matrix_state(empty, "After reset");
    assert(empty.rows() == 0 && empty.cols() == 0);
    std::cout << "Passed!" << std::endl;
}

void test_reset_square_matrix() {
    std::cout << "\nTesting reset on square matrix..." << std::endl;
    Matrix<int> mat = {1, 2, 3, 4};  // 2x2 matrix
    print_matrix_state(mat, "Before reset");
    mat.reset();
    print_matrix_state(mat, "After reset");
    
    // Check dimensions haven't changed
    assert(mat.rows() == 2 && mat.cols() == 2);
    
    // Check all elements are zero
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            if(mat(i,j) != 0) {
                std::cout << "Failed at position (" << i << "," << j << ") with value " << mat(i,j) << std::endl;
                assert(false);
            }
        }
    }
    std::cout << "Passed!" << std::endl;
}

void test_reset_rectangular_matrix() {
    std::cout << "\nTesting reset on rectangular matrix..." << std::endl;
    Matrix<int> mat(3, 2);  // 3x2 matrix
    // Fill with incrementing numbers
    int val = 1;
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            mat(i,j) = val++;
        }
    }
    
    print_matrix_state(mat, "Before reset");
    mat.reset();
    print_matrix_state(mat, "After reset");
    
    // Check dimensions haven't changed
    assert(mat.rows() == 3 && mat.cols() == 2);
    
    // Check all elements are zero
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            if(mat(i,j) != 0) {
                std::cout << "Failed at position (" << i << "," << j << ") with value " << mat(i,j) << std::endl;
                assert(false);
            }
        }
    }
    std::cout << "Passed!" << std::endl;
}

void test_reset_floating_point() {
    std::cout << "\nTesting reset with floating point..." << std::endl;
    Matrix<double> mat(2, 2);
    mat(0,0) = 1.1; mat(0,1) = 2.2;
    mat(1,0) = 3.3; mat(1,1) = 4.4;
    
    print_matrix_state(mat, "Before reset");
    mat.reset();
    print_matrix_state(mat, "After reset");
    
    // Check all elements are 0.0
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            if(mat(i,j) != 0.0) {
                std::cout << "Failed at position (" << i << "," << j << ") with value " << mat(i,j) << std::endl;
                assert(false);
            }
        }
    }
    std::cout << "Passed!" << std::endl;
}

void test_reset_complex_numbers() {
    std::cout << "\nTesting reset with complex numbers..." << std::endl;
    Matrix<std::complex<double>> mat(2, 2);
    mat(0,0) = std::complex<double>(1.0, 1.0);
    mat(0,1) = std::complex<double>(2.0, 2.0);
    mat(1,0) = std::complex<double>(3.0, 3.0);
    mat(1,1) = std::complex<double>(4.0, 4.0);
    
    print_matrix_state(mat, "Before reset");
    mat.reset();
    print_matrix_state(mat, "After reset");
    
    // Check all elements are 0+0i
    std::complex<double> zero(0.0, 0.0);
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            if(mat(i,j) != zero) {
                std::cout << "Failed at position (" << i << "," << j << ") with value " << mat(i,j) << std::endl;
                assert(false);
            }
        }
    }
    std::cout << "Passed!" << std::endl;
}

void test_reset_multiple_times() {
    std::cout << "\nTesting multiple resets..." << std::endl;
    Matrix<int> mat(2, 2);
    
    // First fill and reset
    mat(0,0) = 1; mat(0,1) = 2;
    mat(1,0) = 3; mat(1,1) = 4;
    print_matrix_state(mat, "Initial state");
    
    mat.reset();
    print_matrix_state(mat, "After first reset");
    
    // Fill again and reset
    mat(0,0) = 5; mat(0,1) = 6;
    mat(1,0) = 7; mat(1,1) = 8;
    print_matrix_state(mat, "After filling again");
    
    mat.reset();
    print_matrix_state(mat, "After second reset");
    
    // Check final state
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            if(mat(i,j) != 0) {
                std::cout << "Failed at position (" << i << "," << j << ") with value " << mat(i,j) << std::endl;
                assert(false);
            }
        }
    }
    std::cout << "Passed!" << std::endl;
}

void test_reset_zero_matrix() {
    std::cout << "\nTesting reset on zero matrix..." << std::endl;
    Matrix<int> mat(2, 2);  // Should be initialized with zeros
    print_matrix_state(mat, "Initial zero matrix");
    
    // Verify it's actually zeros
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            if(mat(i,j) != 0) {
                std::cout << "Initial matrix not zero at (" << i << "," << j << ") with value " << mat(i,j) << std::endl;
                assert(false);
            }
        }
    }
    
    mat.reset();
    print_matrix_state(mat, "After reset");
    
    // Check all elements are still zero
    for(size_t i = 0; i < mat.rows(); ++i) {
        for(size_t j = 0; j < mat.cols(); ++j) {
            if(mat(i,j) != 0) {
                std::cout << "Failed at position (" << i << "," << j << ") with value " << mat(i,j) << std::endl;
                assert(false);
            }
        }
    }
    std::cout << "Passed!" << std::endl;
}

void test_default_constructor_equivalence() {
    std::cout << "\nTesting default constructor equivalence..." << std::endl;
    
    Matrix<int> default_mat;  // Default constructor
    Matrix<int> zero_mat(0);  // Matrix(0)
    
    print_matrix_state(default_mat, "Default constructed matrix");
    print_matrix_state(zero_mat, "Matrix(0)");
    
    // Verify they have the same properties
    assert(default_mat.rows() == zero_mat.rows());
    assert(default_mat.cols() == zero_mat.cols());
    assert(default_mat.rows() == 0);
    assert(default_mat.cols() == 0);
    
    // Test reset on both
    default_mat.reset();
    zero_mat.reset();
    
    print_matrix_state(default_mat, "Default matrix after reset");
    print_matrix_state(zero_mat, "Matrix(0) after reset");
    
    // Verify they still have the same properties
    assert(default_mat.rows() == zero_mat.rows());
    assert(default_mat.cols() == zero_mat.cols());
    assert(default_mat.rows() == 0);
    assert(default_mat.cols() == 0);
    
    std::cout << "Passed!" << std::endl;
}

void test_reset_detailed() {
    std::cout << "\nDetailed reset test..." << std::endl;
    
    // Test case 1: Default constructed matrix
    {
        std::cout << "\nTest case 1: Default constructed matrix" << std::endl;
        Matrix<int> mat;
        print_detailed_matrix_state(mat, "Before reset");
        mat.reset();
        print_detailed_matrix_state(mat, "After reset");
    }
    
    // Test case 2: Zero-sized matrix
    {
        std::cout << "\nTest case 2: Zero-sized matrix" << std::endl;
        Matrix<int> mat(0);
        print_detailed_matrix_state(mat, "Before reset");
        mat.reset();
        print_detailed_matrix_state(mat, "After reset");
    }
    
    // Test case 3: 1x1 matrix
    {
        std::cout << "\nTest case 3: 1x1 matrix" << std::endl;
        Matrix<int> mat(1);
        mat(0,0) = 42;
        print_detailed_matrix_state(mat, "Before reset");
        mat.reset();
        print_detailed_matrix_state(mat, "After reset");
        assert(mat(0,0) == 0 && "1x1 matrix element should be 0 after reset");
    }
    
    // Test case 4: Matrix after operations
    {
        std::cout << "\nTest case 4: Matrix after operations" << std::endl;
        Matrix<int> mat(2, 2);
        mat(0,0) = 1; mat(0,1) = 2;
        mat(1,0) = 3; mat(1,1) = 4;
        
        // Do some operations
        mat += 1;
        print_detailed_matrix_state(mat, "After addition");
        
        mat.reset();
        print_detailed_matrix_state(mat, "After reset");
        
        // Verify all elements
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                if(mat(i,j) != 0) {
                    std::cout << "ERROR: Element at (" << i << "," << j << ") = " 
                              << mat(i,j) << " (should be 0)" << std::endl;
                    assert(false);
                }
            }
        }
    }
    
    // Test case 5: Reset multiple times
    {
        std::cout << "\nTest case 5: Multiple resets" << std::endl;
        Matrix<int> mat(2, 2);
        mat(0,0) = 1; mat(0,1) = 2;
        mat(1,0) = 3; mat(1,1) = 4;
        
        print_detailed_matrix_state(mat, "Initial state");
        
        for(int i = 0; i < 3; ++i) {
            mat.reset();
            std::cout << "After reset #" << (i+1) << std::endl;
            print_detailed_matrix_state(mat, "Current state");
            
            // Verify all elements
            for(size_t r = 0; r < mat.rows(); ++r) {
                for(size_t c = 0; c < mat.cols(); ++c) {
                    if(mat(r,c) != 0) {
                        std::cout << "ERROR: Element at (" << r << "," << c << ") = " 
                                  << mat(r,c) << " (should be 0)" << std::endl;
                        assert(false);
                    }
                }
            }
        }
    }
    
    std::cout << "\nAll detailed reset tests passed!" << std::endl;
}

void test_reset_default_values() {
    std::cout << "\nTesting reset with different types and their default values..." << std::endl;
    
    // Test with int (default value should be 0)
    {
        std::cout << "\nTesting int (default = 0):" << std::endl;
        Matrix<int> mat(2, 2);
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                mat(i,j) = 100;  // Set to non-default value
            }
        }
        std::cout << "Before reset:\n" << mat;
        mat.reset();
        std::cout << "After reset:\n" << mat;
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                assert(mat(i,j) == int() && "Should be default int value (0)");
            }
        }
        std::cout << "Passed!" << std::endl;
    }
    
    // Test with double (default value should be 0.0)
    {
        std::cout << "\nTesting double (default = 0.0):" << std::endl;
        Matrix<double> mat(2, 2);
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                mat(i,j) = 3.14;  // Set to non-default value
            }
        }
        std::cout << "Before reset:\n" << mat;
        mat.reset();
        std::cout << "After reset:\n" << mat;
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                assert(mat(i,j) == double() && "Should be default double value (0.0)");
            }
        }
        std::cout << "Passed!" << std::endl;
    }
    
    // Test with string (default value should be empty string)
    {
        std::cout << "\nTesting string (default = \"\"):" << std::endl;
        Matrix<std::string> mat(2, 2);
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                mat(i,j) = "test";  // Set to non-default value
            }
        }
        std::cout << "Before reset:\n" << mat;
        mat.reset();
        std::cout << "After reset:\n" << mat;
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                assert(mat(i,j) == std::string() && "Should be default string value (\"\")");
            }
        }
        std::cout << "Passed!" << std::endl;
    }
    
    // Test with custom type (default value should be 42)
    {
        std::cout << "\nTesting CustomType (default = 42):" << std::endl;
        Matrix<CustomType> mat(2, 2);
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                mat(i,j) = CustomType(100);  // Set to non-default value
            }
        }
        std::cout << "Before reset:\n" << mat;
        mat.reset();
        std::cout << "After reset:\n" << mat;
        for(size_t i = 0; i < mat.rows(); ++i) {
            for(size_t j = 0; j < mat.cols(); ++j) {
                assert(mat(i,j) == CustomType() && "Should be default CustomType value (42)");
            }
        }
        std::cout << "Passed!" << std::endl;
    }
    
    std::cout << "\nAll default value tests passed!" << std::endl;
}

int main() {
    std::cout << "Starting detailed reset tests..." << std::endl;
    test_reset_detailed();
    test_reset_default_values();
    return 0;
} 