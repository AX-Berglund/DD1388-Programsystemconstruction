
#include <cxxtest/TestSuite.h>
#include "Matrix.h"

class MyTestSuite : public CxxTest::TestSuite
{

public:


  static void test_reset( ){
    Matrix<int> m(3);
    m(0,0) = 1;
    m(0,1) = 2;
    m(0,2) = 3;
    m(1,0) = 4;
    m(1,1) = 5;
    m(1,2) = 6;
    m(2,0) = 7;
    m(2,1) = 8;
    m(2,2) = 9;
    //TS_TRACE("Initialized Matrix");
    m.reset();

    //TS_TRACE("Modified Matrix");

      for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) TS_ASSERT(m(i, j) == 0)
      }


  }

  static void test_insert_row( ){

    Matrix<int> m(3);
    m(0,0) = 1;
    m(0,1) = 2;
    m(0,2) = 3;
    m(1,0) = 4;
    m(1,1) = 5;
    m(1,2) = 6;
    m(2,0) = 7;
    m(2,1) = 8;
    m(2,2) = 9;


    m.insert_row(1);

    TS_ASSERT(m(1,0) == 0)
    TS_ASSERT(m(1,1) == 0)
    TS_ASSERT(m(1,2) == 0)

  }

  static void test_append_row(){
    Matrix<int> m(3);
    m(0,0) = 1;
    m(0,1) = 2;
    m(0,2) = 3;
    m(1,0) = 4;
    m(1,1) = 5;
    m(1,2) = 6;
    m(2,0) = 7;
    m(2,1) = 8;
    m(2,2) = 9;


    m.append_row(1);

    TS_ASSERT(m(2,0) == 0)
    TS_ASSERT(m(2,1) == 0)
    TS_ASSERT(m(2,2) == 0)


    TS_ASSERT_LESS_THAN(3 , m.rows())



  }

  static void test_remove_row(){
    Matrix<int> m(3);
    m(0,0) = 1;
    m(0,1) = 2;
    m(0,2) = 3;
    m(1,0) = 4;
    m(1,1) = 5;
    m(1,2) = 6;
    m(2,0) = 7;
    m(2,1) = 8;
    m(2,2) = 9;

    m.remove_row(1);

    TS_ASSERT_LESS_THAN(m.rows(),3)


  }

  static void test_insert_column(){
    Matrix<int> m(3);
    m(0,0) = 1;
    m(0,1) = 2;
    m(0,2) = 3;
    m(1,0) = 4;
    m(1,1) = 5;
    m(1,2) = 6;
    m(2,0) = 7;
    m(2,1) = 8;
    m(2,2) = 9;

    m.insert_column(1);

    TS_ASSERT_LESS_THAN(3, m.cols())

  }

  static void test_append_column(){
    Matrix<int> m(3);
    m(0,0) = 1;
    m(0,1) = 2;
    m(0,2) = 3;
    m(1,0) = 4;
    m(1,1) = 5;
    m(1,2) = 6;
    m(2,0) = 7;
    m(2,1) = 8;
    m(2,2) = 9;
    //std::cout << "Initialized Matrix m: " << std::endl;
    //std::cout << m << std::endl;

    m.append_column(1);
    //std::cout << "Modified m: " << std::endl;
    //std::cout << m << std::endl;
    TS_ASSERT_LESS_THAN(3 , m.cols())

    TS_ASSERT(m(0,2) == 0)
    TS_ASSERT(m(1,2) == 0)
    TS_ASSERT(m(2,2) == 0)

  }

  static void test_remove_column(){
    Matrix<int> m(3);
    m(0,0) = 1;
    m(0,1) = 2;
    m(0,2) = 3;
    m(1,0) = 4;
    m(1,1) = 5;
    m(1,2) = 6;
    m(2,0) = 7;
    m(2,1) = 8;
    m(2,2) = 9;
    //std::cout << "Initialized Matrix m: " << std::endl;
    //std::cout << m << std::endl;
    m.remove_column(1);
    //std::cout << "Modified m: " << std::endl;
    //std::cout << m << std::endl;
    TS_ASSERT_LESS_THAN(m.cols() , 3)

  }


  static void test_mult_operator(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << m1 << std::endl;

    Matrix<int> m2(2,2);
    m2(0,0) = 1;
    m2(0,1) = 2;
    m2(1,0) = 3;
    m2(1,1) = 4;
    //std::cout << m2 << std::endl;

    Matrix<int> m3 = m1 * m2;
    //std::cout << m3 << std::endl;

    TS_ASSERT(m3.rows() == m1.rows())
    TS_ASSERT(m3.cols() == m2.cols())


  }


  static void test_plus_operator(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << m1 << std::endl;

    Matrix<int> m2(2,2);
    m2(0,0) = 1;
    m2(0,1) = 2;
    m2(1,0) = 3;
    m2(1,1) = 4;
    //std::cout << m2 << std::endl;

    Matrix<int> m3 = m1 + m2;
    //std::cout << m3 << std::endl;

    TS_ASSERT(m3(0,0)==2)
    TS_ASSERT(m3(0,1)==4)
    TS_ASSERT(m3(1,0)==6)
    TS_ASSERT(m3(1,1)==8)


  }


  static void test_minus_operator(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << m1 << std::endl;

    Matrix<int> m2(2,2);
    m2(0,0) = 1;
    m2(0,1) = 2;
    m2(1,0) = 3;
    m2(1,1) = 4;
    //std::cout << m2 << std::endl;

    Matrix<int> m3 = m1 - m2;
    //std::cout << m3 << std::endl;

    TS_ASSERT(m3(0,0)==0)
    TS_ASSERT(m3(0,1)==0)
    TS_ASSERT(m3(1,0)==0)
    TS_ASSERT(m3(1,1)==0)


  }


  static void test_mult_eq_operator(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << "This is m1: " << std::endl;
    //std::cout << m1 << std::endl;

    Matrix<int> m2(2,2);
    m2(0,0) = 1;
    m2(0,1) = 2;
    m2(1,0) = 3;
    m2(1,1) = 4;
    //std::cout << "This is m2: " << std::endl;
    //std::cout << m2 << std::endl;

    m1 *= m2;

    //std::cout << "This is m1 afer m1 *= m2: " << std::endl;
    //std::cout << m1 << std::endl;



    TS_ASSERT(m1(0,0)==7)
    TS_ASSERT(m1(0,1)==10)
    TS_ASSERT(m1(1,0)==15)
    TS_ASSERT(m1(1,1)==22)

    TS_ASSERT(m2(0,0)==1)
    TS_ASSERT(m2(0,1)==2)
    TS_ASSERT(m2(1,0)==3)
    TS_ASSERT(m2(1,1)==4)



    //std::cout << "This is m2 afer m1 *= m2: " << std::endl;
    //std::cout << m2 << std::endl;

  }

  static void test_plus_eq_operator(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << "This is m1: " << std::endl;
    //std::cout << m1 << std::endl;

    Matrix<int> m2(2,2);
    m2(0,0) = 1;
    m2(0,1) = 2;
    m2(1,0) = 3;
    m2(1,1) = 4;
    //std::cout << "This is m2: " << std::endl;
    //std::cout << m2 << std::endl;

    m1 += m2;

    TS_ASSERT(m1(0,0)==2)
    TS_ASSERT(m1(0,1)==4)
    TS_ASSERT(m1(1,0)==6)
    TS_ASSERT(m1(1,1)==8)

    TS_ASSERT(m2(0,0)==1)
    TS_ASSERT(m2(0,1)==2)
    TS_ASSERT(m2(1,0)==3)
    TS_ASSERT(m2(1,1)==4)

    //std::cout << "This is m1 afer m1 += m2: " << std::endl;
    //std::cout << m1 << std::endl;

    //std::cout << "This is m2 afer m1 += m2: " << std::endl;
    //std::cout << m2 << std::endl;

  }


  static void test_minus_eq_operator(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << "This is m1: " << std::endl;
    //std::cout << m1 << std::endl;

    Matrix<int> m2(2,2);
    m2(0,0) = 1;
    m2(0,1) = 2;
    m2(1,0) = 3;
    m2(1,1) = 4;
    //std::cout << "This is m2: " << std::endl;
    //std::cout << m2 << std::endl;

    m1 -= m2;

    //std::cout << "This is m1 afer m1 -= m2: " << std::endl;
    //std::cout << m1 << std::endl;

    //std::cout << "This is m2 afer m1 -= m2: " << std::endl;
    //std::cout << m2 << std::endl;

    TS_ASSERT(m1(0,0)==0)
    TS_ASSERT(m1(0,1)==0)
    TS_ASSERT(m1(1,0)==0)
    TS_ASSERT(m1(1,1)==0)

    TS_ASSERT(m2(0,0)==1)
    TS_ASSERT(m2(0,1)==2)
    TS_ASSERT(m2(1,0)==3)
    TS_ASSERT(m2(1,1)==4)

  }

  static void test_Matrix(){

    Matrix<int> m1;
    Matrix<int> m2(0);

    TS_ASSERT(m1.rows() == 0)
    TS_ASSERT(m2.cols() == 0)

  }


  static void test_Matrix_dim(){

    Matrix<int> m(4);
    TS_ASSERT(m.rows() == 4)
    TS_ASSERT(m.cols() == 4)

    for(int i = 0 ; i < 4 ; i++){
      for(int j = 0 ; j < 4 ; j++){
        TS_ASSERT( m(i,j) == 0 )

      }
    }
  }


  static void test_Matrix_row_col(){
    Matrix<int> m(4,3);

    TS_ASSERT(m.rows() == 4)
    TS_ASSERT(m.cols() == 3)

  }


  static void test_Matrix_std_init_list(){

    Matrix<int> m = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    TS_ASSERT(m.rows() == m.cols())

    TS_ASSERT(m(0,0) == 1)
    TS_ASSERT(m(0,1) == 2)
    TS_ASSERT(m(0,2) == 3)
    TS_ASSERT(m(1,0) == 4)
    TS_ASSERT(m(1,1) == 5)
    TS_ASSERT(m(1,2) == 6)
    TS_ASSERT(m(2,0) == 7)
    TS_ASSERT(m(2,1) == 8)
    TS_ASSERT(m(2,2) == 9)
  }

  static void test_copy_constructor(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << "This is m1: " << std::endl;
    //std::cout << m1 << std::endl;


    Matrix<int> m2 = m1;

    TS_ASSERT(m1(0,0) == m2(0,0))
    TS_ASSERT(m1(0,1) == m2(0,1))
    TS_ASSERT(m1(1,0) == m2(1,0))
    TS_ASSERT(m1(1,1) == m2(1,1))


    //std::cout << "This is m2 afer Matrix<int> m2 = m1: " << std::endl;
    //std::cout << m2 << std::endl;

    //std::cout << "This is m1 afer Matrix<int> m2 = m1: " << std::endl;
    //std::cout << m1 << std::endl;


  }


  static void test_move_constructor(){

    Matrix<int> m1(2,2);
    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << "This is m1: " << std::endl;
    //std::cout << m1 << std::endl;


    Matrix<int> m2 = std::move(m1);

    //TS_ASSERT_IS_NAN(m1);

    TS_ASSERT(m2(0,0)==1)
    TS_ASSERT(m2(0,1)==2)
    TS_ASSERT(m2(1,0)==3)
    TS_ASSERT(m2(1,1)==4)

    //std::cout << "This is m2 afer Matrix<int> m2 = std::move(m1): " << std::endl;
    //std::cout << m2 << std::endl;
    //std::cout << "This is m1 afer Matrix<int> m2 = std::move(m1): " << std::endl;
    //std::cout << m1 << std::endl;
  }


  static void test_move_assign_operator(){


    Matrix<int> m1(2,2);
    //Matrix<int> * point = &m1;

    m1(0,0) = 1;
    m1(0,1) = 2;
    m1(1,0) = 3;
    m1(1,1) = 4;
    //std::cout << "This is m1: " << std::endl;
    //std::cout << m1 << std::endl;

    //std::cout << *point << std::endl;
    Matrix<int> m2(2,2);
    m2(0,0) = 1;
    m2(0,1) = 1;
    m2(1,0) = 1;
    m2(1,1) = 1;
    //std::cout << "This is m2: " << std::endl;
    //std::cout << m2 << std::endl;



    m2 = m1;

    //std::cout << *point << std::endl;

    TS_ASSERT(m2(0,0)==1)
    TS_ASSERT(m2(0,1)==2)
    TS_ASSERT(m2(1,0)==3)
    TS_ASSERT(m2(1,1)==4)

    //TS_ASSERT(*point == m1);


    //std::cout << "This is m2 after m2 = m1: " << std::endl;
    //std::cout << m2 << std::endl;

    //std::cout << "This is m1 after  m2 = m1: " << std::endl;
    //std::cout << m1 << std::endl;

  }

  static void test_rows(){

    Matrix<int> m(4);
    //std::cout << m.rows() << std::endl;

    TS_ASSERT(m.rows()==4)

  }

  static void test_cols(){

    Matrix<int> m(4);
    //std::cout << m.cols() << std::endl;
    TS_ASSERT(m.cols()==4)

  }


  static void test_identity(){

    Matrix<int> m = identity<int>(5);

    TS_ASSERT(m.cols()==5)
    TS_ASSERT(m.rows()==5)

    for(int i = 0 ; i < 5 ; i++){
      for(int j = 0 ; j < 5 ; j++){
        if(i==j){
          TS_ASSERT( m(i,j) == 1 )
        }
      }
    }
  }

  static void test_overload_const(){

    Matrix<int> m(2,2);
    TS_ASSERT(m(0,0)==0)
    TS_ASSERT(m(0,1)==0)
    TS_ASSERT(m(1,0)==0)
    TS_ASSERT(m(1,1)==0)



  }

  static void test_overload_non_const(){

    Matrix<int> m(2,2);

    m(0,0) = 1;
    m(0,1) = 2;
    m(1,0) = 3;
    m(1,1) = 4;

    TS_ASSERT(m(0,0)==1)
    TS_ASSERT(m(0,1)==2)
    TS_ASSERT(m(1,0)==3)
    TS_ASSERT(m(1,1)==4)


  }




};
