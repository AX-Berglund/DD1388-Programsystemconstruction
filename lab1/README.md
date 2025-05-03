# Lab 01


## Dependencies


Create a file *ABmain.cpp* in 01 with the following content
```C++
class A {
  B * b;
  int method(int x) { return x; }
};

struct B {
  A a;
  int memberfunction(int x) { return x; }
};

int main() {
  A a;
  B b;
  int x = b.memberfunction( 3 );
}
```

The file does not compile because the compiler does not know what *struct B* is when compiling *class A*. 
Solve this by doing a forward declaration of *B* by writing *struct B;* at the top of the file. Compile the program. 

Change the type of member variables *a* and *b* and make *b* an object and *a* a pointer.

```C++
struct B;
class A {
  B b;
  int method(int x) { return x; }
};

struct B {
  A * a;
  int memberfunction(int x) { return x; }
};
// ....
```

Compile the program. Note the compile error message you get. A class
forward instruction is not enough. To compile *class A* the compiler
now needs to know the layout of *struct B* as defined in the struct
definition in order to compile.

### header files and implementation files

Please use the below header and implementation files, in total 5 files:

1. a main file *mainAB.cpp* with the following content
```C++
#include "A.h"
#include "B.h"
int main() {
  A a;
  B b;
  int x = b.memberfunction( 3 );
}
```

2. implementation file *A.cpp*
```C++
#include "A.h"
int A::method(int x) { return x; }
```

3. implementation file *B.cpp*
```C++
#include "B.h"
int B::memberfunction(int x) { return x; }
```

4. header file *A.h*
```C++
//use guards or pragma once

// add includes and forward declarations below

// don't change the class definition
class A
{
public:
    B b;
    int method(int x);
};
```

5. header file *B.h*
```C++
//use guards or pragma once

// add includes and/or forward declarations here

// don't change the definition below
struct B
{
    A *a;
    int memberfunction(int x);
};
```


Update the two headerfiles *A.h* and *B.h* containing the class
definition. Use a forward declaration and, if needed, include the
class definition of the other
class. Do use
[include guards](https://en.wikipedia.org/wiki/Include_guard) or
[pragma once](https://en.wikipedia.org/wiki/Pragma_once) to avoid
multiple includes.

Compile the programs one by one
```
> g++ -c A.cpp
> g++ -c B.cpp
> g++ mainAB.cpp A.o B.o
```

or alltogether

```
> g++ -c mainAB.cpp A.cpp B.cpp
```


#### g++ compiler questions

Put questions and answers in a file _inquiry.md_.

#### Where can you find the manual to g++?

####  What is the purpose of _-Wall_ and _-g_, when passed as arguments to _g++_?

#### What is the difference between an object file, and an executable?

#### What in the example above is a forward declaration?

#### Why is it not possible to have class A containing a B object and B containing an A object? 

`class A { B b; };`
`class B { A a; };`


## Assignment: an improved world of hello

_hello, world_ is a classic program that dates back to 1974, first published
in a paper titled _Programming in C: A tutorial_. The program has one
simple purpose; to print "_hello, world_".

Since the typical implementation is trivial, your task is to write a more
versatile alternative, having the following semantics:

```
> ./hello
Hello, world!
> ./hello "DD1387"
Hello, DD1387!
> ./hello "KTH" 3
Hello, KTH KTH KTH!
> ./hello "KTH" 0
> ./hello "KTH" 2
Hello, KTH KTH!
> ./hello "Malcom X" NaN
error: 2nd argument must be an integral greater than zero!
> ./hello kth dd1387 3
error: Too many arguments!
```

_This assignment is not an exercise in object-oriented programming (OOP), but
a mere introduction to the fundamental parts of C/C++_

### Files

Create the following files under the directory 01 in your personal cprog Git repository.

_main.cpp_:

```cpp
#include <utility> // std::pair
#include "hello.h"
int main (int argc, char* argv[]) {
  std::pair<const char *, int> p = parse_args (argc ,argv);
  if (p.second != -1)
    hello (p.first, p.second);
}
```

_hello.h_:
```cpp
#include <utility>  // std::pair

void hello (const char * name, int count);
std::pair<const char *, int> parse_args (int argc, char * argv[]);
```

_hello.cpp_:
```cpp
#include <iostream>

#include "hello.h"

void hello (const char * name, int count) {
  // TODO
}

std::pair<const char *, int> parse_args (int argc, char * argv[]) {
  // TODO
  return std::make_pair ("TODO", 1);
}
```

### Requirements

* _main.cpp_ contains the definition of the applications _main_-function.
There is no need for you to modify this file, but please make sure that
you understand what is written in it.

* _hello.cpp_ has a corresponding _.h_-header that contains
_forward-declarations_ for the functions you are to implement.

* This header, _hello.h_, is included (_#include_) by
_main.cpp_, and should be included by _hello.cpp_.

* _hello.cpp_ shall be compiled separately, resulting in an
object file that is to be linked into the resulting executable.

* You shall implement a function named _parse\_args_ in a separate
_translation unit_ named _hello.cpp_.
This function is responsible for parsing/interpreting the command line
arguments passed to the application, and shall return a
[_std::pair_](http://en.cppreference.com/w/cpp/utility/pair)
with what to print, and how many times to print it.

* _parse\_args_ shall handle all input errors by returning _-1_
as the second value of the returned _std::pair_, as well as printing
a suitable error message on _stderr_.

* You shall implement a function named _hello_ in a separate
_translation unit_ named _hello.cpp_ (i.e. the same file that
shall contain the implementation of _parse_args_).

* _hello_ is responsible for printing the _hello world_-string on
_stdout_ with the following semantics;

* If the value _zero_ is passed as the second parameter,
    nothing shall be printed.

* If a value greater than _zero_ is passed as the second argument
(_count_), _"Hello, "_ shall be printed followed by
_count_ space-delimited occurrences of the first argument.
The output shall end with an exclamation mark, followed by a new-line.
*Note*: hello ("KTH", 3)* shall print _Hello, KTH KTH KTH!_ (see the
  previous example invocations of the program for more information).

* Correct output from your program shall be printed through
_std::cout_, whereas potential error diagnostics (detected by
_parse\_args_) shall be printed through _std::cerr_.

* Your implementation, _hello.cpp_, shall be [uploaded to Kattis.](https://kth.kattis.com/courses/DD1388/cprog24/assignments/i6u3vn)

* For us to be able to grade your Hello World program you must register on kattis (cprog24) by clicking the link [_I am a student taking this course and I want to register for it on Kattis_](https://kth.kattis.com/courses/DD1388/cprog24). Then click on the "Hello Hello World" assignment, and then on "Join the Session".

### Hints

* The argument named _argc_ to _main_ will contain the number of
arguments passed to your application. Remember that the name of the
executable counts to this number.

* The second argument, _argv_, will provide access to the individual
arguments passed to your application.

* _std::atoi_ from _<cstdlib>_ can be used to convert a
_char const *_ to an integer. If the function is unable to interpret
the data as an integer, it will return _0_.


### Kattis test cases hints

1. No command line arguments are given
2. Only one argument is given
3. Do you print the argument as many times as needed correctly?
4. What happens if you print something 0 times?
5. Do you print the argument as many times as needed correctly?
6. What happens is more than 2 arguments are given? Where do you stream your output?
7. Can you print something NaN times?
8. Do you print the argument as many times as needed correctly?
9. Can you print something negative times? Where do you stream your output?

* Remember! Your error messages have specifications!



#### Hello world questions

#### What is the purpose of _std::cout_, _std::cerr_, and _std::clog_, respectively?

#### How does #include work?



## Unit testing

Create a file _count_if_followed_by.cpp_ with the following content

```cpp
// .-------------------------------------------------------
// |        count_if_followed_by (data, len, a, b);
// |
// | About: Returns the number of occurances of
// |        a followed by b in the range [data, data+len).
// '-------------------------------------------------------

int count_if_followed_by (char const * p, int len, char a, char b) {
  int        count = 0;
  char const * end = p + len;

  while (p != end) {
    if (*p == a && *(p+1) == b)
      count += 1;

    ++p;
  }

  return count;
}
```

Create a corresponding header file _count_if_followed_by.h_
```cpp
int count_if_followed_by (char const * p, int len, char a, char b);
```

### Task

There is an intentional bug in the definition of
_count_if_followed_by_; it will potentially access one element outside
the range specified.  Collectively, bugs of this sort is most often referred to
as "_off-by-one errors_".

```C++
// expected: result == 0
// outcome: result == 1 (!!!)

char const data[4] = {'G','G','X','G'};
int  const result  = count_if_followed_by (data, 3, 'X', 'G');
```

You are to write tests using [google test framework](https://github.com/google/googletest).
See the [getting started section](https://github.com/google/googletest?tab=readme-ov-file#getting-started)


### Requirements

* Implement at least three (3) different tests of your own that tests
the correct, and incorrect, behavior of _count_if_followed_by_.


### What to test

It is important to test boundary conditions. For linked list and
trees, the empty list, a list with one item, the last item. For
arrays, the first and last (size) index).

Remember to test that properexceptions are thrown according to lab specifications.

#### unit test questions

#### Why is it important to test the boundary conditions of an implementation, especially in the case of _count_if_followed_by_?

#### Describe how your testcase tests if a pointer is accessing an element outside the range specified


### Good luck