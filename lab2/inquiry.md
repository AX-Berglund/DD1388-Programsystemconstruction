# Inquiry


1. What did you learn from this assignment?
2. What was the hardest part (or parts) in this assignment?
3. Which of your class methods or non-member functions returns a copy?
4. Which of your class methods or non-member functions returns a reference?
5. How many tests do you need at minimum to test the abs function?
6. Describe and motivate how your implementation of operator= works
7. What constructors/functions are called when writing the statement Complex k = 3 + 5_i;
8. Describe and motivate how your implementation of operator+= -= /= *= = works with regard to return value
9. What is the rule of three in C++. Look it up in a C++ book or on the web.
10. With regard to the rule of three, do you need to explicitly define and implement the copy-constructor in this assignment?
11. The literal i has an underscore before it. Why is that? Look it up in the c++11 draft section 17.6.4.3.5 and explain. Has there been any changes regarding this matter in the new c++17 draft

## Answers

1. I learnt more about how to implement a class and its member functions, such as friend functions which allow access to the protected private members of the class, which was necessary for operator functions. I also got more familiar with the i- and ostream operators and how they work.
2. The hardest part was to implement the literal operator with suffix _i and separate imaginary value from the real value. I did not understand how that would work until I learnt it. It was also hard to decide what each function should return.
3. operator+()  operator-()  operator+ - * /  abs()  operator""_i   operator<<
4. operator=  operator+=   operator-=  operator*=   operator/= operator== operator!= operator< operator>>
5. I suppuse 4 times to test posetive and negative values for both real and imag values
6. It copies one object to the other, checks for selfassignment, and retruns a reference to the object copied to, and leaves the object copied from untouched (unless it is chaining)
7. First the constructor creates an object k = 3 which creates an object k = (3,0), and then the literal operator""_i runs and returns a new object with only the _i value in a new object temp = (0,5). Thereafter the operator+ runs followed by the constructor again z = k + temp which becomes z = (3,5)
8. These returns reference values. The reason for this is to save memory and time when working with larger objects. It also allows chaining
9. The rule of three is that, If a class needs one of the following functions, it probably needs all three to avoid complications.
        The functions are:
          - Copy constructor 
          - Copy assignment operator
          - Destructor
10. In this case, it works without a copy constructor, but it is still recommended to implement a separate copy constructor. Now it uses the default copy constructor. But this will not hold for more complicated applications. The default constructor copies the data members from the source object to the target object
11. The underscore between the literal value and its suffix was introduced to avoid conflicts with existing identifiers and future language features. In c++17 the underscore is optional
