# Lab 4: Lambdas and smart pointers

In this assignment you will work with [lambdas](http://en.cppreference.com/w/cpp/language/lambda) and [smart pointers](http://en.cppreference.com/w/cpp/memory).

## No Kattis

This assignment does not need to be uploaded to Kattis


## Questions to answer

Put questions and answers in a file _inquiry.md_ and do put relevant code examples if needed for clarity.

#### What did you learn in this assignment?


#### What is a capture list in a lambda expression?


#### What does & mean inside the capture list?


#### When could capturing data by reference [&] be useful?


#### What does {4} in the code below do?
```
        A * p = new A {4} ;
```

#### Why is it a compile error to call foo with a unique_ptr without a move?
```
        foo(pa);
```

#### Was there ever a memory leak when calling foo2 with a shared pointer?


#### What is the use of a weak_ptr?


#### How do you create a unique_ptr with a special deleter?


#### What is _decltype_ ?


#### What is std::function?


You will need to include the following libraries in this
assignment. Namespace std:: is used for clarity.
```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

using namespace std;
```


# Lambdas

```c++
//...
{
    vector<int> v = {1, 3, 4, 5, 6, 7, 8, 9};
    // printing v
    cout << "vector v:" << endl;
    for (auto x : v) { cout << x << " ";};
    cout << endl;

```

Write a for_each statement that uses a lambda expression to print
odd numbers in vector v.

```
    for_each(v.cbegin(), v.cend(), // YOUR LAMBDA HERE
```

* Write another for_each statement that changes the values in v by
multipliying all odd numbers by 2.

* Write a for_each statement that changes the vector elements by
  adding the size of the vector to all elements.


* Write a lambda function on our own that changes any data of your choice
  outside the scope of the lambda by capturing with [ & ].

example:
```c++

   //...
   int OUTSIDEDATA

   // ....  [ & OUTSIDEDATA ]( // YOUR LAMBDA

```

# Smart pointers

The following code will be used

```c++
struct A {
    int data;

};

void foo(unique_ptr<A> p) {
    cout << p->data << endl;
}

void foo2(shared_ptr<A> p) {
    cout << p->data << endl;
}

```

Define a unique_ptr to A inside an arbitrary scope and print the data

```

    {
        unique_ptr<A> pa(new A {4} );
        cout << pa -> data;
```


Try calling _foo_ with your unique_ptr. There is a compile error
because you are calling by value, trying to copy the pointer.

```
        foo(pa);
```

Fix the compile error by using move when calling foo. Run valgrind (see
preparations) on your executable and verify that there are no memory
leaks.

### Shared ptr

Declare a shared pointer to A and print the data

```c++
        shared_ptr<A> sa(new A {5});
        cout << sa -> data;
```

Call foo2 first normally and then by moving. Run valgrind on both executables. Is there a memory leak?

```c++
        foo2(sa);            // check with valgrind
        //foo2(move(sa));    // check with valgrind
```

### Weak pointer

Constructing a weak pointer as a shared pointer generates a compile error

```C++
        weak_ptr<A> wa(new A {5});
```

Construct a weak pointer to the previous shared pointer and try print the
data. There will be a compile error.

```C++
        weak_ptr<A> wa = sa;
        cout << wa->data;
```

Use the _lock_ member function to print the data field.


### Circular dependencies

Given BhasA and AhasB

```c++
struct BhasA;

struct AhasB {
    AhasB(shared_ptr<BhasA> b) : m_b(b)  {
        resource = new int[4];
    };

    shared_ptr<BhasA> m_b;
    int * resource;

    ~AhasB() {delete [] resource;}
    AhasB(const AhasB &) = delete;
    void operator=(const AhasB &) = delete;
};

struct BhasA {
    BhasA() {resource = new int[4];};

    shared_ptr<AhasB> m_a;
    int * resource;

    ~BhasA() {delete [] resource;}
    BhasA(const BhasA &) = delete;
    void operator=(const BhasA &) = delete;
};

```

Declare one instance each of AhasB and BhasA and link them.

```C++
        shared_ptr<BhasA> bptr(new BhasA);
        shared_ptr<AhasB> aptr(new AhasB(bptr));

        bptr->m_a=aptr;
```

There is a memory leak when you run valgrind on the code because of
the circular dependency. Fix the memory leak by changing one of the
shared_ptr members to a weak pointer.

### Using a deleter

Given B

```c++
struct B {
    B() { b = new int[4]; }

    int * b;
    ~B() { delete [] b; }
    B(const B &) = delete;
    void operator= (const B & ) = delete;
};
```

Unless the compiler detects it, there will a memory leak when declaring a unique_ptr as below. Verify
the memory leak with valgrind.

```c++
        unique_ptr<B> pb(new B[2]);
```

The memory leak is because the unique_ptr assumes it points to a single
object not to an array.

In order to fix the memory leak you need to create a function that
does a correct deletion of the objects. 

Write a lambda function that does a correct deletion of the array


```c++
        auto deleter = // YOUR LAMBDA HERE
        unique_ptr<B, decltype(deleter)> pb2(new B[2], deleter);
```


If you know the signature of your lambda function you can declare it
with the _function_ keyword directly instead of using auto

```c++
        function<void(B*)> fb = // YOUR LAMBDA
```

It is thus possible to declare the unique_ptr in one row

```c++
        unique_ptr<B, function<void(B*)> > pb1(new B[2],  // YOUR LAMBDA
```

_Note: In later standards its possible to specify the kind of pointer in the template parameter_
```c++
        unique_ptr< B[] > pb(new B[2]);    // Note B[]
```