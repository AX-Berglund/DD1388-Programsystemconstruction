#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>
#include <cassert>
#include <type_traits>
#include <string>
#include <sstream>

//
// DD1388 - Lab 2: The matrix
//

template <typename T>
class Matrix {

    //value evaluates to either true or false
    static_assert(std::is_move_constructible<T>::value, "T must be move-constructible");
    static_assert(std::is_move_assignable<T>::value, "T must be move-assignable");

public:
    // constructors and assignment operators
    Matrix();
    explicit Matrix(size_t dim);
    Matrix(size_t rows, size_t cols);
    Matrix(const std::initializer_list<T> & list);

    Matrix(Matrix<T> & other);//COPY CONSTRUCTOR - Matrix<int> m2 = m1;
    Matrix(Matrix<T> && other) noexcept;//MOVE CONSTRUCTOR

    //Copy Assignment Operator
    Matrix<T> & operator=(const Matrix<T> & other);

    //Move Assignment Operator for the Matrix<T> object
    Matrix<T> & operator=(Matrix<T> && other) noexcept;

    //DESTRUCTOR
    ~Matrix();

    // accessors
    size_t rows() const;
    size_t cols() const;

    //m(i,j)
    T & operator()(size_t row, size_t col);
    const T & operator()(size_t row, size_t col) const;
    
    // Scalar operations
    Matrix<T> operator+(const T& scalar) const;
    Matrix<T> operator-(const T& scalar) const;
    Matrix<T> operator*(const T& scalar) const;

    void operator+=(const T& scalar);
    void operator-=(const T& scalar);
    void operator*=(const T& scalar);
    
    // Matrix operations
    Matrix<T> operator*(const Matrix<T> & other) const;
    Matrix<T> operator+(const Matrix<T> & other) const;
    Matrix<T> operator-(const Matrix<T> & other) const;

    bool operator==(const Matrix<T>& m) const;
    bool operator!=(const Matrix<T>& m) const;

    void operator*=(const Matrix<T> & other);
    void operator+=(const Matrix<T> & other);
    void operator-=(const Matrix<T> & other);

    // methods
    void reset();
    void transpose();

    void insert_row(size_t row);
    void append_row(size_t row);
    void remove_row(size_t row);
    void insert_column(size_t col);
    void append_column(size_t col);
    void remove_column(size_t col);

    // Iterators
    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin() {
        return m_vec;
    }
    
    iterator end() {
        return m_vec + m_capacity;
    }


private:
    size_t m_rows;
    size_t m_cols;
    size_t m_capacity;
    T * m_vec;  // m_vec is a pointer to an array of elements of type T
};

// input/output operators
template<typename T>
std::istream & operator>>(std::istream & is, Matrix<T> & m) {
    std::vector<T> elements;
    T value;
    
    // Read all elements from the stream
    while (is >> value) {
        elements.push_back(value);
    }
    
    // Clear the stream state
    is.clear();
    
    // Calculate dimensions
    size_t total_elements = elements.size();
    size_t cols = 0;
    
    // Find the number of columns by looking for the first newline
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    while (iss >> value) {
        cols++;
    }
    
    // If no columns found, assume it's a square matrix
    if (cols == 0) {
        size_t root = sqrt(total_elements);
        if (root * root != total_elements) {
            throw std::runtime_error("Number of elements is not a square number");
        }
        cols = root;
    }
    
    size_t rows = total_elements / cols;
    if (rows * cols != total_elements) {
        throw std::runtime_error("Invalid matrix dimensions");
    }
    
    // Create the matrix with the calculated dimensions
    Matrix<T> m_temp(rows, cols);
    m = std::move(m_temp);
    
    // Fill the matrix with the read elements
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            m(i, j) = elements[i * cols + j];
        }
    }
    
    return is;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const Matrix<T> & m) {
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.cols(); ++j) {
            os << m(i, j);
            if (j < m.cols() - 1) {
                os << " ";
            }
        }
        if (i < m.rows() - 1) {
            os << std::endl;
        }
    }
    return os;
}

// functions
template<typename T>
Matrix<T> identity(size_t dim);

// Implementation

template<typename T>
Matrix<T>::Matrix() : Matrix(0) {  // Delegate to the single-parameter constructor with 0
}

template<typename T>
Matrix<T>::Matrix(size_t dim) {
    m_rows = dim;
    m_cols = dim;
    m_capacity = dim * dim;
    // Always allocate at least one element to maintain consistency
    m_vec = new T[m_capacity ? m_capacity : 1];
    for(size_t i = 0; i < m_capacity; i++) {
        m_vec[i] = T();
    }
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) {
    m_rows = rows;
    m_cols = cols;
    m_capacity = rows * cols;
    // Always allocate at least one element to maintain consistency
    m_vec = new T[m_capacity ? m_capacity : 1];
    for(size_t i = 0; i < m_capacity; i++) {
        m_vec[i] = T();
    }
}

template<typename T>
Matrix<T>::Matrix(const std::initializer_list<T> & list) {
    size_t list_size = list.size();
    size_t root = sqrt(list_size);
    if(root * root != list_size) {
        throw std::out_of_range("Number of elements is not a square number\n");
    }

    m_rows = root;
    m_cols = root;
    m_capacity = m_rows * m_cols;
    m_vec = new T[m_capacity];
    std::copy(list.begin(), list.end(), m_vec);
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> & other) {
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = new T[m_capacity];
    for (size_t i = 0; i < m_capacity; i++) {
        m_vec[i] = other.m_vec[i];
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T> && other) noexcept {
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = other.m_vec;  // Take ownership of the memory

    // Reset the source object
    other.m_vec = nullptr;
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_capacity = 0;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
    if (this == &other) {
        return *this;
    }

    // Deallocate existing memory
    delete[] m_vec;

    // Copy dimensions and allocate new memory
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = new T[m_capacity];

    // Copy the data
    for (size_t i = 0; i < m_capacity; i++) {
        m_vec[i] = other.m_vec[i];
    }

    return *this;
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) noexcept {
    if (this == &other) {
        return *this;
    }

    // Deallocate existing memory
    delete[] m_vec;

    // Move properties from other
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_capacity = other.m_capacity;
    m_vec = other.m_vec;  // Take ownership of memory

    // Reset the source object
    other.m_vec = nullptr;
    other.m_rows = 0;
    other.m_cols = 0;
    other.m_capacity = 0;

    return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& m) const {
    if (m_rows != m.m_rows || m_cols != m.m_cols) {
        return false;
    }

    for (size_t i = 0; i < m_capacity; i++) {
        if (m_vec[i] != m.m_vec[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T>& m) const {
    return !(*this == m);
}

template<typename T>
Matrix<T>::~Matrix() {
    delete[] m_vec;
    m_vec = nullptr;
    m_rows = 0;
    m_cols = 0;
    m_capacity = 0;
}

template<typename T>
size_t Matrix<T>::rows() const {
    return m_rows;
}

template<typename T>
size_t Matrix<T>::cols() const {
    return m_cols;
}

template<typename T>
T & Matrix<T>::operator()(size_t row, size_t col) {
    if(row >= m_rows || col >= m_cols) {
        throw std::out_of_range("Matrix indices out of bounds");
    }
    return m_vec[row * m_cols + col];
}

template<typename T>
const T & Matrix<T>::operator()(size_t row, size_t col) const {
    if(row >= m_rows || col >= m_cols) {
        throw std::out_of_range("Matrix indices out of bounds");
    }
    return m_vec[row * m_cols + col];
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const T& scalar) const {
    Matrix<T> result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j) + scalar;
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const T& scalar) const {
    Matrix<T> result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j) - scalar;
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    Matrix<T> result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j) * scalar;
        }
    }
    return result;
}

template<typename T>
void Matrix<T>::operator+=(const T& scalar) {
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            (*this)(i, j) += scalar;
        }
    }
}

template<typename T>
void Matrix<T>::operator-=(const T& scalar) {
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            (*this)(i, j) -= scalar;
        }
    }
}

template<typename T>
void Matrix<T>::operator*=(const T& scalar) {
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            (*this)(i, j) *= scalar;
        }
    }
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> & other) const {
    if (m_cols != other.m_rows) {
        throw std::runtime_error("Incompatible matrix dimensions for multiplication");
    }
    
    Matrix<T> result(m_rows, other.m_cols);
    for (size_t i = 0; i < result.m_rows; i++) {
        for (size_t j = 0; j < result.m_cols; j++) {
            T sum = T();
            for (size_t k = 0; k < m_cols; k++) {
                sum += (*this)(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Incompatible matrix dimensions for addition");
    }
    
    Matrix<T> result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & other) const {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Incompatible matrix dimensions for subtraction");
    }
    
    Matrix<T> result(m_rows, m_cols);
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

template<typename T>
void Matrix<T>::operator*=(const Matrix<T> & other) {
    if (m_cols != other.m_rows) {
        throw std::runtime_error("Incompatible matrix dimensions for multiplication");
    }
    
    Matrix<T> result = (*this) * other;
    *this = std::move(result);
}

template<typename T>
void Matrix<T>::operator+=(const Matrix<T> & other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Incompatible matrix dimensions for addition");
    }
    
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            (*this)(i, j) += other(i, j);
        }
    }
}

template<typename T>
void Matrix<T>::operator-=(const Matrix<T> & other) {
    if (m_rows != other.m_rows || m_cols != other.m_cols) {
        throw std::runtime_error("Incompatible matrix dimensions for subtraction");
    }
    
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            (*this)(i, j) -= other(i, j);
        }
    }
}

// Non-member operator overloads for scalar operations
template<typename T>
Matrix<T> operator+(const T& scalar, const Matrix<T>& matrix) {
    return matrix + scalar;  // Use the member operator we defined
}

template<typename T>
Matrix<T> operator-(const T& scalar, const Matrix<T>& matrix) {
    Matrix<T> result(matrix.rows(), matrix.cols());
    for (size_t i = 0; i < matrix.rows(); i++) {
        for (size_t j = 0; j < matrix.cols(); j++) {
            result(i, j) = scalar - matrix(i, j);
        }
    }
    return result;
}

template<typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix) {
    return matrix * scalar;  // Use the member operator we defined
}



template<typename T>
void Matrix<T>::reset() {
    delete [] m_vec;
    m_cols = m_rows = m_capacity = 0;
    m_vec = new T[m_capacity]();
}

template<typename T>
void Matrix<T>::transpose() {
    Matrix<T> temp(m_cols, m_rows);
    
    for (size_t r = 0; r < m_rows; r++) {
        for (size_t c = 0; c < m_cols; c++) {
            temp(c, r) = (*this)(r, c);
        }
    }
    
    *this = std::move(temp);
}



template<typename T>
void Matrix<T>::insert_row(size_t row) {
    if (row > m_rows) {
        throw std::out_of_range("Row index out of range");
    }
    
    Matrix<T> result(m_rows + 1, m_cols);
    
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j);
        }
    }
    
    // New row will be initialized with T() by default
    
    for (size_t i = row; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i + 1, j) = (*this)(i, j);
        }
    }
    
    *this = std::move(result);
}

template<typename T>
void Matrix<T>::append_row(size_t row) {
    if (row >= m_rows) {
        throw std::out_of_range("Row index out of range");
    }
    
    Matrix<T> result(m_rows + 1, m_cols);
    
    for (size_t i = 0; i <= row; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j);
        }
    }
    
    // New row will be initialized with T() by default
    
    for (size_t i = row + 1; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i + 1, j) = (*this)(i, j);
        }
    }
    
    *this = std::move(result);
}

template<typename T>
void Matrix<T>::remove_row(size_t row) {
    if (row >= m_rows) {
        throw std::out_of_range("Row index out of range");
    }
    
    Matrix<T> result(m_rows - 1, m_cols);
    
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i, j) = (*this)(i, j);
        }
    }
    
    for (size_t i = row + 1; i < m_rows; i++) {
        for (size_t j = 0; j < m_cols; j++) {
            result(i - 1, j) = (*this)(i, j);
        }
    }
    
    *this = std::move(result);
}

template<typename T>
void Matrix<T>::insert_column(size_t col) {
    if (col > m_cols) {
        throw std::out_of_range("Column index out of range");
    }
    
    Matrix<T> result(m_rows, m_cols + 1);
    
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < col; j++) {
            result(i, j) = (*this)(i, j);
        }
        
        // New column will be initialized with T() by default
        
        for (size_t j = col; j < m_cols; j++) {
            result(i, j + 1) = (*this)(i, j);
        }
    }
    
    *this = std::move(result);
}

template<typename T>
void Matrix<T>::append_column(size_t col) {
    if (col >= m_cols) {
        throw std::out_of_range("Column index out of range");
    }
    
    Matrix<T> result(m_rows, m_cols + 1);
    
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j <= col; j++) {
            result(i, j) = (*this)(i, j);
        }
        
        // New column will be initialized with T() by default
        
        for (size_t j = col + 1; j < m_cols; j++) {
            result(i, j + 1) = (*this)(i, j);
        }
    }
    
    *this = std::move(result);
}

template<typename T>
void Matrix<T>::remove_column(size_t col) {
    if (col >= m_cols) {
        throw std::out_of_range("Column index out of range");
    }
    
    Matrix<T> result(m_rows, m_cols - 1);
    
    for (size_t i = 0; i < m_rows; i++) {
        for (size_t j = 0; j < col; j++) {
            result(i, j) = (*this)(i, j);
        }
        
        for (size_t j = col + 1; j < m_cols; j++) {
            result(i, j - 1) = (*this)(i, j);
        }
    }
    
    *this = std::move(result);
}

template<typename T>
Matrix<T> identity(size_t dim) {
    Matrix<T> m(dim);
    for (size_t i = 0; i < dim; ++i) {
        m(i, i) = T(1);
    }
    return m;
}

#endif // MATRIX_H