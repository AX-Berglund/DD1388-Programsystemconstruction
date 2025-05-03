# Lab 2: The matrix

In this assignment you will implement a matrix class. You may need to refresh your knowledge on basic matrix arithmetics. The matrix should be implemented with a one-dimensional array (*m_vec*) which means you need to use some simple arithmetic to access a matrix index (i, j). If the number of rows is only one, the matrix will essentially behave like a vector. Random access to an element should be on average constant O(1).
The first element (0, 0) is at m_vec[0].

## Questions to answer

Write your answers in _02/inquiry.md_.

#### What did you learn from this assignment?


#### What was hardest to implement in this assignment?


#### How many methods/functions have you implemented?


#### How many methods/functions have you tested?


#### Describe and motivate how your implementation of operator= works


#### When do you need to resize in your code?


#### When you resize your matrix, are you able to move the elements?


#### Why do you need to implement a const-version of the accessor operator?


#### Is it possible to call std::sort() to sort your matrix using begin() and end()?


#### What other kind of iterators, besides random access iterators, are there in C++? 




## Requirements


Appropriate methods should be declared *const*.

Methods should throw std::out_of_range if the dimensions do not match the method call.

The matrix should handle necessary memory allocation internally without
memory leaks. If the matrix needs to expand, the internal vector must be resized. Use valgrind or fsanitize to verify your code.

```c++
template class T>
class Matrix {
public:
   // constructors

   // operators

   // methods

private:
   size_t m_rows;
   size_t m_cols;
   size_t m_capacity;
   T * m_vec;
}
```

The full code template can be found at _lab\_02/Matrix.h_.

### Constructors and assignment operators

Some of this constructors might seem strange but they are here for you to practice C++.


* It should be possible to construct the matrix with a single number. The matrix created should be a square matrix with initial elements set to the default element of the type.

```
   Matrix<int> m(3);
   m [ 0 0 0
       0 0 0
       0 0 0 ]
```

* It should be possible to _default-construct_ the container, which
  should be semantically equivalent to Matrix\<T\>(0).

* It should be possible to construct a matrix with two parameters
  specifying the rows and columns of the matrix. 

* You should implement a copy-constructor and a destructor. _Note_ modifying a copied
  matrix should not change the contents of the copied-from matrix.

*   It should not be possible to instantiate the class template unless the
    specified element type is both *[moveConstructible](https://en.cppreference.com/w/cpp/types/is_move_constructible)* and
    *moveAssignable*. Use _static_assert_ with an appropriate error message, to
    *[moveAssignable](https://en.cppreference.com/w/cpp/types/is_move_assignable)*. Use _static_assert_ with an appropriate error message, to
    make sure that this is the case.

* Appropriate constructors should be explicit. If someone, without
  intending to, types m = 3 there should be a compile error.

* You should implement a copy-assignment operator, and although assigning
  a matrix to itself might seem silly, make sure it is handled correctly.


* Implement a move-constructor and a move-assignment operator taking
   another matrix potentially of a different size. Move constructors
   can reduce the number of copies in a C++-program.


* Implement a constructor taking _std::initializer_list_. This constructor can only
  construct square matrices. If the number of elements is not an even square root
  std::out_of_range should be thrown. The first elements defines the first row and
  then the next rows in sequence.



### Accessors

* implement rows() and cols() which returns number of rows and columns respectively.

* Implement the function operator to access/modify elements. Make a *const* version as well.

```c++
   Matrix<int> m(3);
   m(1, 1) = 3;
   const Matrix<int> & mref = m;
   std::cout << mref(1, 1);
```

### Operators

For both scalar and matrix operations:

* Implement * + - which should be chainable.

* Implement *= += -= as non chainable.

Writing and reading from stdin and stdout in human friendly (readable) format.

* Implement operator<< and operator>> and make them compatible. If you write to a file, you should be able to read the matrix from the same file. The exact format is up to you but do make it human-readable (use a line break after each row).

### Methods/functions

* Implement _reset()_ method which clears the underlying array (removes it) and resets the capacity (including rows/cols) of the matrix.

* Implement the function _identity(unsigned int)_ which returns a square identity matrix where all elements but the diagonal are set to 0 and the diagonal values to 1. This function does only have to work with numeric types such as _int_ or _double_.

Implement the following [Microsoft(R) Excel](https://en.wikipedia.org/wiki/Microsoft_Excel) inspired methods:

* Implement *insert_row* which inserts a row of zeroes before a given row number.

* Implement *append_row* which inserts a row of zeroes after a given row number.

* Implement *remove_row* which erases the entire row at a given row number.

* Implement *insert_column* which inserts a column of zeroes before a given column number.

* Implement *append_column* which inserts a column of zeroes after a given column number.

* Implement *remove_column* which erases the entire column at a given column number.

### Iterators, do typedef T* as iterator

* Implement *begin()* which returns the pointer to the first element of the matrix.

* Implement *end()* which returns the pointer to the element after the last element.
  
  When being typedef, these will essentially work as random access iterators and can be used by <algorithm> library.

   
   
## Tests

For each method/function implemented. Implement at least one test (one method call).

Use googletest for testing. 

Your tests should automatically compare your code's behaviour to the expected behaviour using various assert-like functions provided to you by your test framework of choice. Here are tutorials for [googletest](https://google.github.io/googletest/primer.html).

**Note:** Your tests must not leak memory, this is a requirement in all labs. For more information please read the [README.md](README.md) file under the "General Requirements" section. To test this you need to use a tool such as Valgrind or fsanitize. During the presentation you may be asked about this.

* Your implementation, _Matrix.h_, shall be [uploaded to Kattis.](https://kth.kattis.com/courses/DD1388/cprog24/assignments/xku7cr). 
   
### Kattis test cases hints

1. Check for your Default Construction
2. Something is probably wrong in your Normal Construction
3. Your Copy Construction might not be correctly implemented
4. The problem might be in your Move Construction Assignment
5. Calling reset does not work as expected
6. Excel operators: Your Excel Row operations might be incorrect
7. Excel operators: Your Excel Column operations might be incorrect
8. Your Iterator implementation might be incorrect
9. Exception safety is not properly implemented
10. Testing on Input/Output exhibits problems (input-output streams might not be compatible)
   - Note: when you create a matrix from a stream, you cannot know how many numbers the matrix should contain. So make sure the shape of the matrix does not dictate the shape of the streamed content.
11.  The Identity Matrix implementation might be incorrect
