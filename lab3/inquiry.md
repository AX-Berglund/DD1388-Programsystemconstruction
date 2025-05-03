# Inquiry

Write your answers below and include the questions. Do copy relevant code to your answers so that both questions and answers are in context 

1. What did you learn from this assignment?

2. What was hardest to implement in this assignment?

3. How many methods/functions have you implemented?

4. How many methods/functions have you tested?

5. Describe and motivate how your implementation of operator= works

6. When do you need to resize in your code?

7. When you resize your matrix, are you able to move the elements?

8. Why do you need to implement a const-version of the accessor operator?

9. Is it possible to call std::sort() to sort your matrix using begin() and end()?

10. What other kind of iterators, besides random access iterators, are there in C++?

## Answers


1. I learnt what difference between constructors and assignment operators is. I learnt that the move operator deletes the data that 
it is being moved from. I learnt how to implement the input and output operators. I used new and delete a lot which was educational. 

2. Some implementations were hard because the lack of information. for example, I was not sure how the "*" operator should have been implemented so i did a few different implementations and then settled for one. It was hard to resize the matrix and insert rows and cols etc.

3. I have implemented 25 methods/functions and 3 non member functions: is, os, identity )

4. I have tested all functions while implementing them. I have not been able to test it with valgrind for memory leaks tho.  
From my analysis, the code does not generate any obvious memory leaks, but it could do so if the certain operations are not handled correctly.  
For example, if the move constructor or move assignment operator are not properly implemented, memory can be leaked when a matrix object is moved. Additionally, if the insert_row, append_row, remove_row, insert_column, append_column, or remove_column methods do not properly allocate or deallocate memory, memory leaks could occur.

5. That would be the Move or COPY assignment operator.  
The COPY assignment operator first check so there is no self assignment. If not, it deallocates whatever data is in the current object. Then allocates  
new memory with the same dimensions as the matrix being copied from, and set each element in the new matrix equal to each element in the matrix that is  
being copied. Then it returns the new object, without modifying the matrix being copied from.  
The Move assignment operator does basically the same thing but before returning the object it deletes the copied from object

6. I need to resize the matrix when the dimensions must change, for example when appending, inserting, removing rows and collumns. Or when copying or moving one matrix to another matrix with different dimensions.

7. No, since the matrix being moved to is of the samt dimensions as the matrix being moved from. 

8. To avoid errors of assigning new values to the object, and make them read only

9. Yes, std::sort(m1.begin(), m1.end()); sorts matrix m1 with begin() and end()

10. Bidirectinoal iterators - can access elements in a range in both directions
  Forward iterators - each value is read once and iterated to the next
  Input and Output iterator
  
