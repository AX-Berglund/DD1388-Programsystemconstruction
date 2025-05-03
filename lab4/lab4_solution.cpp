#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <functional>

using namespace std;

struct A {
    int data;
};

void foo(unique_ptr<A> p) {
    cout << p->data << endl;
}

void foo2(shared_ptr<A> p) {
    cout << p->data << endl;
}

struct BhasA;

struct AhasB {
    AhasB(shared_ptr<BhasA> b) : m_b(b) {
        resource = new int[4];
    };

    shared_ptr<BhasA> m_b; // Change this to weak_ptr to fix the circular dependency
    int * resource;

    ~AhasB() {
        delete[] resource;
        cout << "AhasB destructor called" << endl;
    }
    AhasB(const AhasB &) = delete;
    void operator=(const AhasB &) = delete;
};

struct BhasA {
    BhasA() {
        resource = new int[4];
    };

    // Changed to weak_ptr to fix circular dependency
    weak_ptr<AhasB> m_a;
    int * resource;

    ~BhasA() {
        delete[] resource;
        cout << "BhasA destructor called" << endl;
    }
    BhasA(const BhasA &) = delete;
    void operator=(const BhasA &) = delete;
};

struct B {
    B() { 
        b = new int[4];
        cout << "B constructor called" << endl;
    }

    int * b;
    ~B() { 
        delete[] b;
        cout << "B destructor called" << endl;
    }
    B(const B &) = delete;
    void operator= (const B & ) = delete;
};

int main() {
    // LAMBDAS
    {
        vector<int> v = {1, 3, 4, 5, 6, 7, 8, 9};
        // printing v
        cout << "Vector v:" << endl;
        for (auto x : v) { cout << x << " "; }
        cout << endl;

        // Print odd numbers in vector v
        cout << "Odd numbers in v:" << endl;
        for_each(v.cbegin(), v.cend(), [](int x) {
            if (x % 2 != 0) {
                cout << x << " ";
            }
        });
        cout << endl;

        // Multiply all odd numbers by 2
        for_each(v.begin(), v.end(), [](int& x) {
            if (x % 2 != 0) {
                x *= 2;
            }
        });
        
        cout << "After multiplying odd numbers by 2:" << endl;
        for (auto x : v) { cout << x << " "; }
        cout << endl;

        // Add size of vector to all elements
        for_each(v.begin(), v.end(), [size = v.size()](int& x) {
            x += size;
        });
        
        cout << "After adding vector size to all elements:" << endl;
        for (auto x : v) { cout << x << " "; }
        cout << endl;

        // Lambda that changes data outside its scope using capture by reference
        int outsideData = 10;
        cout << "outsideData before lambda: " << outsideData << endl;
        
        auto changeOutsideData = [&outsideData]() {
            outsideData *= 2;
            cout << "Inside lambda, outsideData is now: " << outsideData << endl;
        };
        
        changeOutsideData();
        cout << "outsideData after lambda: " << outsideData << endl;
    }

    cout << "\n--- SMART POINTERS ---\n" << endl;

    // UNIQUE POINTER
    {
        cout << "Unique pointer example:" << endl;
        
        // Define a unique_ptr to A and print the data
        unique_ptr<A> pa(new A {4});
        cout << "pa->data: " << pa->data << endl;
        
        // Call foo using move to transfer ownership
        cout << "Calling foo with move(pa):" << endl;
        foo(move(pa));
        
        // At this point, pa no longer owns the object
        cout << "pa is " << (pa ? "not null" : "null") << " after move" << endl;
    }
    
    // SHARED POINTER
    {
        cout << "\nShared pointer example:" << endl;
        
        // Declare a shared pointer to A and print data
        shared_ptr<A> sa(new A {5});
        cout << "sa->data: " << sa->data << endl;
        cout << "Use count: " << sa.use_count() << endl;
        
        // Call foo2 normally (makes a copy)
        cout << "Calling foo2(sa):" << endl;
        foo2(sa);
        cout << "sa still valid after foo2 call, use count: " << sa.use_count() << endl;
        
        // Call foo2 with move
        cout << "Calling foo2(move(sa)):" << endl;
        foo2(move(sa));
        
        // sa no longer owns the resource
        cout << "sa is " << (sa ? "not null" : "null") << " after move" << endl;
    }
    
    // WEAK POINTER
    {
        cout << "\nWeak pointer example:" << endl;
        
        shared_ptr<A> sa(new A {6});
        cout << "Created shared_ptr sa with data: " << sa->data << endl;
        
        // Create a weak_ptr to the shared_ptr
        weak_ptr<A> wa = sa;
        cout << "Created weak_ptr wa pointing to sa" << endl;
        
        // Use lock() to access the data
        if (auto locked_ptr = wa.lock()) {
            cout << "Accessed data through weak_ptr lock(): " << locked_ptr->data << endl;
        } else {
            cout << "Failed to lock weak_ptr (object no longer exists)" << endl;
        }
        
        // Release the shared_ptr
        sa.reset();
        cout << "Reset shared_ptr sa" << endl;
        
        // Try to access through weak_ptr again
        if (auto locked_ptr = wa.lock()) {
            cout << "Accessed data through weak_ptr lock(): " << locked_ptr->data << endl;
        } else {
            cout << "Failed to lock weak_ptr (object no longer exists)" << endl;
        }
    }
    
    // CIRCULAR DEPENDENCIES
    {
        cout << "\nCircular dependencies example:" << endl;
        
        shared_ptr<BhasA> bptr(new BhasA);
        shared_ptr<AhasB> aptr(new AhasB(bptr));
        
        // Link them together
        bptr->m_a = aptr;
        
        cout << "Created circular reference between AhasB and BhasA" << endl;
        cout << "BhasA use count: " << bptr.use_count() << endl;
        cout << "AhasB use count: " << aptr.use_count() << endl;
    }
    
    // USING A DELETER
    {
        cout << "\nCustom deleter example:" << endl;
        
        // This would cause a memory leak because unique_ptr assumes single object
        // unique_ptr<B> pb(new B[2]);
        
        // Create a custom deleter using lambda
        auto deleter = [](B* ptr) {
            cout << "Custom deleter called" << endl;
            delete[] ptr;
        };
        
        unique_ptr<B, decltype(deleter)> pb2(new B[2], deleter);
        cout << "Created unique_ptr with custom deleter" << endl;
        
        // Alternative with std::function
        function<void(B*)> fb = [](B* ptr) {
            cout << "std::function deleter called" << endl;
            delete[] ptr;
        };
        
        unique_ptr<B, function<void(B*)>> pb1(new B[2], [](B* ptr) {
            cout << "Inline function deleter called" << endl;
            delete[] ptr;
        });
        cout << "Created another unique_ptr with std::function deleter" << endl;
        
        // In newer C++ standards:
        // unique_ptr<B[]> pb(new B[2]);
    }
    
    cout << "\nAll scopes closed, destructors should be called" << endl;
    return 0;
}