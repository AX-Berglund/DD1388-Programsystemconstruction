# Lab 3: Complex numbers


For this lab you will create a class that represents a complex number. In essence, you will create a class that can handle addition, subtraction, multiplication and division. Do investigate what constructors are called and how or if they should be implemented.

How complex numbers work can be found out by reading the [wikipedia page](https://en.wikipedia.org/wiki/Complex_number). You may refresh [conjugate algebra](https://en.wikipedia.org/wiki/Conjugate_%28algebra%29) when implementing division. You can also reference how the [standard library](http://en.cppreference.com/w/cpp/numeric/complex) implementation works. You will need to use at least c++11 (-std=c++11) for this assignment. From now on, do use at least c++11 for the upcoming assignments.

## Kattis

* Your declaration and implementation files, _Complex.h_ and _Complex.cpp_, shall be [uploaded to Kattis](https://kth.kattis.com/courses/DD1388/cprog24/assignments/m4bnvt).


## Questions to answer

Put questions and answers in a file _inquiry.md_ and do put relevant code examples if needed for clarity.

#### What did you learn from this assignment?

#### What was the hardest part (or parts) in this assignment?

#### Which of your class methods or non-member functions returns a copy?

#### Which of your class methods or non-member functions returns a reference?

#### How many tests do you need at minimum to test the _abs_ function?

#### Describe and motivate how your implementation of operator= works

#### What constructors/functions are called when writing the statement Complex k = 3 + 5_i;

#### Describe and motivate how your implementation of operator+= -= /= *= = works with regard to return value

#### What is the rule of three in C++. Look it up in a C++ book or on the web.

#### With regard to the rule of three, do you need to explicitly define and implement the copy-constructor in this assignment?

#### The literal _i_ has an underscore before it. Why is that? Look it up in the [c++11 draft](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3376.pdf) section 17.6.4.3.5 and explain. Has there been any changes regarding this matter in the [new c++17 draft](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4659.pdf)




## Functions
In the style of [cppreference](http://en.cppreference.com/w/cpp/numeric/complex) the following things should be defined:

| Member functions |  - |
|  ---                 | --- |
| (constructor)        | constructs a complex number (see guidance below) |
| `operator=`            | assigns the contents |
| `real`                 | accesses the real part of the complex number |
| `imag`                 | accesses the imaginary part of the complex number |
| `operator+=` `-=` `/=` `*=`  | compound assignment of two complex numbers or a complex and a scalar |



| Non-member functions  | - |
| ---             | ---|
| `operator+` `-`     | applies unary operators to complex numbers |
| `operator+` `-` `*` `/` | performs complex number arithmetics on two complex values or a complex and a scalar |
| `operator==` `!=`   | compares two complex numbers or a complex and a scalar |
| `real`            | returns the real component |
| `imag`            | returns the imaginary component |
| `abs`             | returns the magnitude of a complex number |
| `operator<`       | returns true if the magnitude of the left complex number is lesser than the right complex number, and false otherwise |
| `operator<<`           |  Writes to output stream the complex number in the form _(real,imaginary)_ |
| `operator>>`           | Reads a complex number from is. The supported formats are real, (real) and (real,imaginary) Where the input must be convertible to Double |
| `operator""_i`    | Forms a complex literal representing an imaginary number (note the underscore) |

## Specific Requirements

These following requirements need to be fulfilled to pass this lab.

* You have to write your own tests that verify that everything works. We will look very closely on these tests, and they are expected to cover every unique possible scenario, better write too many than too few.

* Write instructions in your 03/Readme.md file on how to compile the tests. If you're using a Makefile, make sure that you have the following rules:
  * _make all_ builds your class and testprogram
  * _make tests_ runs your tests

* The type that you use to save the values should be doubles.

* You should be able to answer what function/functions will be called for all types of assignments and constructions. Feel free to experiment with trace outputs (prints) in the functions to learn what is called. Remove, comment or use your preprocessor flags to hide your trace outputs in the final submission.

## Guidance
These are the constructor signatures that you will need:

* Complex();
* Complex(double real);     // _Note: make this constructor [non explicit](http://en.cppreference.com/w/cpp/language/converting_constructor) to allow expressions such as z = 3;_
* Complex(double real, double imaginary);
* Complex(const Complex &rhs);

This thing enables you to write complex numbers in literal form.
* constexpr Complex operator""_i(long double arg);

Any *constexpr* is resolved in compile time. That means that any
constructor called by *operator""_i* must also be resolved in compile
time. To ensure that, use [member initializer list, whose syntax is the
colon character :, followed by the comma-separated list of one or more
member-initializers](https://en.cppreference.com/w/cpp/language/constructor)
and let the body of the constructor be empty.

### Make your own design decisions

operator+= -= /= *= =

You need to think about what the return type of operator= and
operator+= -= /= *= should be. The design decision is up to you. Given
_Complex x; Complex y;_ should all of these work or only a few? Make
your own design decisions and *motivate* them.

* Complex x; Complex y;
* x = y + 1;
* x = y + y + 1 + 5;     // chaining
* x = 2 + y;
* x += y += 4;           // chaining
* x = y = 0;             // chaining

## Basic test examples

Examples of things that should work. Note you must test more extensively on your own.

* Complex x;
* Complex x2 = 5;
* Complex y(6, 2);
* Complex z = x + y;
* Complex k = 3 + 5_i;
* k -= 5 + 1_i * Complex(5, 3);
* std::cout << Complex(6, 6) / 6 << std::endl;

### Kattis test cases hints

1. This test checks the Construction of an object
2. Is assignment of complex numbers happening correctly?
3. A problem might exist in Arithmetic Assignments (+=, -=, *=, /=)
4. Your boolean operators (==, !=, <) might be faulty
5. Does the absolute value behave as it should?
6. Arithmetic operations between scalars-complex and complex-complex might not behave as they should
7. The implementation of  the operator””_i might be faulty
8. Does Input/output behave as it should? (are the streams compatible?)

