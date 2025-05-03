# Inquiry.md

## What did you learn in this assignment?
In this assignment, I learned about lambda expressions and smart pointers in C++. Lambda expressions provide a concise way to define anonymous functions inline, making code more readable when using algorithms like `for_each`. Smart pointers (unique_ptr, shared_ptr, and weak_ptr) automate memory management to prevent memory leaks and provide safer memory handling compared to raw pointers. I also learned about special deleters, circular dependencies, and how to use decltype with smart pointers.

## What is a capture list in a lambda expression?
A capture list in a lambda expression specifies which variables from the surrounding scope are accessible within the lambda body and how they are captured. The capture list is defined inside square brackets `[]` at the beginning of a lambda expression. Variables can be captured by value or by reference.

## What does & mean inside the capture list?
The `&` symbol inside a capture list indicates that variables are captured by reference rather than by value. This means the lambda can access and modify the original variables from the outer scope.

## When could capturing data by reference [&] be useful?
Capturing data by reference is useful when:
1. You need to modify variables from the enclosing scope
2. You want to avoid copying large objects for performance reasons
3. You need to access objects that cannot be copied (like unique_ptr)
4. You need to work with the most up-to-date values of variables that might change in the outer scope
5. You want to return values from a lambda through reference parameters

## What does {4} in the code below do?
```cpp
A * p = new A {4};
```
This is an example of list initialization (introduced in C++11). It creates a new instance of struct A and initializes its `data` member to 4. It's equivalent to creating an object and then assigning the value, but in a more concise syntax.

## Why is it a compile error to call foo with a unique_ptr without a move?
```cpp
foo(pa);
```
It's a compile error because `unique_ptr` cannot be copied, only moved. This is by design to maintain the "unique ownership" semantics - there should only ever be one `unique_ptr` owning a resource at any time. When passing a `unique_ptr` by value to a function like `foo`, the compiler attempts to make a copy, which is disallowed. Using `move(pa)` explicitly transfers ownership to the function parameter.

## Was there ever a memory leak when calling foo2 with a shared_ptr?
No, there was never a memory leak when calling `foo2` with a shared pointer, regardless of whether we used `move` or not. This is because `shared_ptr` maintains a reference count that keeps track of how many owners the resource has. When passing by value, the count increases, and when the function returns, the count decreases. The memory is only freed when the count reaches zero.

## What is the use of a weak_ptr?
A `weak_ptr` is used to observe a shared object without affecting its lifetime. It's particularly useful for:
1. Breaking circular references between `shared_ptr` objects that would cause memory leaks
2. Implementing caches or observers that don't need to keep objects alive
3. Checking if an object is still alive before accessing it (by using the `lock()` method to get a `shared_ptr`)

Unlike `shared_ptr`, a `weak_ptr` doesn't increase the reference count of the managed object, so it doesn't prevent deletion when all `shared_ptr` instances go out of scope.

## How do you create a unique_ptr with a special deleter?
To create a `unique_ptr` with a special deleter, you specify the deleter type as the second template parameter and provide the deleter instance as the second constructor argument:

```cpp
auto deleter = [](T* ptr) { /* custom deletion logic */ };
unique_ptr<T, decltype(deleter)> ptr(new T, deleter);
```

Alternatively, you can use `std::function`:

```cpp
unique_ptr<T, function<void(T*)>> ptr(new T, [](T* ptr) { /* custom deletion logic */ });
```

## What is decltype?
`decltype` is a C++11 keyword that returns the type of an expression or entity. It's useful when you need to declare variables with types that depend on template parameters or complex expressions, without having to manually specify the exact type. For example, `decltype(x + y)` gives the type that results from adding `x` and `y`.

## What is std::function?
`std::function` is a general-purpose polymorphic function wrapper that can store, copy, and invoke any callable target - functions, lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members. It allows you to abstract the callable entity behind a common type, making it useful for callbacks, storing functions in containers, and more.