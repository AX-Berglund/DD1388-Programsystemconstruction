#include "Matrix.h"
#include "string"

void test_reset(){
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
  std::cout << "Initialized Matrix m: " << std::endl;
  std::cout << m << std::endl;
  m.reset();
  std::cout << "Modified Matrix m: " << std::endl;
  std::cout << m << std::endl;
}

void test_insert_row(){
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
  std::cout << "Initialized Matrix m: " << std::endl;
  std::cout << m << std::endl;
  m.insert_row(1);
  std::cout << "Modified Matrix m: " << std::endl;
  std::cout << m << std::endl;
}

void test_append_row(){
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
  std::cout << "Initialized Matrix m: " << std::endl;
  std::cout << m << std::endl;
  m.append_row(1);
  std::cout << "Modified Matrix m: " << std::endl;
  std::cout << m << std::endl;
}

void test_remove_row(){
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
  std::cout << "Initialized Matrix m: " << std::endl;
  std::cout << m << std::endl;
  m.remove_row(1);
  std::cout << "Modified m: " << std::endl;
  std::cout << m << std::endl;
}

void test_insert_column(){
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
  std::cout << "Initialized Matrix m: " << std::endl;
  std::cout << m << std::endl;
  m.insert_column(1);
  std::cout << "Modified m: " << std::endl;
  std::cout << m << std::endl;
}

void test_append_column(){
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
  std::cout << "Initialized Matrix m: " << std::endl;
  std::cout << m << std::endl;
  m.append_column(1);
  std::cout << "Modified m: " << std::endl;
  std::cout << m << std::endl;
}

void test_remove_column(){
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
  std::cout << "Initialized Matrix m: " << std::endl;
  std::cout << m << std::endl;
  m.remove_column(1);
  std::cout << "Modified m: " << std::endl;
  std::cout << m << std::endl;
}



void test_mult_operator(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << m1 << std::endl;

  Matrix<int> m2(2,2);
  m2(0,0) = 1;
  m2(0,1) = 2;
  m2(1,0) = 3;
  m2(1,1) = 4;
  std::cout << m2 << std::endl;

  Matrix<int> m3 = m1 * m2;
  std::cout << m3 << std::endl;

}

void test_plus_operator(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << m1 << std::endl;

  Matrix<int> m2(2,2);
  m2(0,0) = 1;
  m2(0,1) = 2;
  m2(1,0) = 3;
  m2(1,1) = 4;
  std::cout << m2 << std::endl;

  Matrix<int> m3 = m1 + m2;
  std::cout << m3 << std::endl;

}

void test_minus_operator(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << m1 << std::endl;

  Matrix<int> m2(2,2);
  m2(0,0) = 1;
  m2(0,1) = 2;
  m2(1,0) = 3;
  m2(1,1) = 4;
  std::cout << m2 << std::endl;

  Matrix<int> m3 = m1 - m2;
  std::cout << m3 << std::endl;

}


void test_mult_eq_operator(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << "This is m1: " << std::endl;
  std::cout << m1 << std::endl;

  Matrix<int> m2(2,2);
  m2(0,0) = 1;
  m2(0,1) = 2;
  m2(1,0) = 3;
  m2(1,1) = 4;
  std::cout << "This is m2: " << std::endl;
  std::cout << m2 << std::endl;

  m1 *= m2;

  std::cout << "This is m1 afer m1 *= m2: " << std::endl;
  std::cout << m1 << std::endl;

  std::cout << "This is m2 afer m1 *= m2: " << std::endl;
  std::cout << m2 << std::endl;

}

void test_plus_eq_operator(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << "This is m1: " << std::endl;
  std::cout << m1 << std::endl;

  Matrix<int> m2(2,2);
  m2(0,0) = 1;
  m2(0,1) = 2;
  m2(1,0) = 3;
  m2(1,1) = 4;
  std::cout << "This is m2: " << std::endl;
  std::cout << m2 << std::endl;

  m1 += m2;

  std::cout << "This is m1 afer m1 += m2: " << std::endl;
  std::cout << m1 << std::endl;

  std::cout << "This is m2 afer m1 += m2: " << std::endl;
  std::cout << m2 << std::endl;

}

void test_minus_eq_operator(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << "This is m1: " << std::endl;
  std::cout << m1 << std::endl;

  Matrix<int> m2(2,2);
  m2(0,0) = 1;
  m2(0,1) = 2;
  m2(1,0) = 3;
  m2(1,1) = 4;
  std::cout << "This is m2: " << std::endl;
  std::cout << m2 << std::endl;

  m1 -= m2;

  std::cout << "This is m1 afer m1 -= m2: " << std::endl;
  std::cout << m1 << std::endl;

  std::cout << "This is m2 afer m1 -= m2: " << std::endl;
  std::cout << m2 << std::endl;

}


void test_Matrix(){

  Matrix<int> m1;
  std::cout << m1 << std::endl;

  Matrix<int> m2(0);
  std::cout << m2 << std::endl;

}

void test_Matrix_dim(){

  Matrix<int> m(4);
  std::cout << m << std::endl;
}

void test_Matrix_row_col(){
  Matrix<int> m(4,3);
  std::cout << m << std::endl;
}

void test_Matrix_std_init_list(){

  Matrix<int> m = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << m << std::endl;


}

void test_copy_constructor(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << "This is m1: " << std::endl;
  std::cout << m1 << std::endl;


  Matrix<int> m2 = m1;

  std::cout << "This is m2 afer Matrix<int> m2 = m1: " << std::endl;
  std::cout << m2 << std::endl;

  std::cout << "This is m1 afer Matrix<int> m2 = m1: " << std::endl;
  std::cout << m1 << std::endl;


}

void test_move_constructor(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << "This is m1: " << std::endl;
  std::cout << m1 << std::endl;


  Matrix<int> m2 = std::move(m1);

  std::cout << "This is m2 afer Matrix<int> m2 = std::move(m1): " << std::endl;
  std::cout << m2 << std::endl;

  std::cout << "This is m1 afer Matrix<int> m2 = std::move(m1): " << std::endl;
  std::cout << m1 << std::endl;

}

void test_move_assign_operator(){

  Matrix<int> m1(2,2);
  m1(0,0) = 1;
  m1(0,1) = 2;
  m1(1,0) = 3;
  m1(1,1) = 4;
  std::cout << "This is m1: " << std::endl;
  std::cout << m1 << std::endl;

  Matrix<int> m2(2,2);
  m2(0,0) = 1;
  m2(0,1) = 1;
  m2(1,0) = 1;
  m2(1,1) = 1;
  std::cout << "This is m2: " << std::endl;
  std::cout << m2 << std::endl;


  m2 = m1;

  std::cout << "This is m2 after m2 = m1: " << std::endl;
  std::cout << m2 << std::endl;

  std::cout << "This is m1 after  m2 = m1: " << std::endl;
  std::cout << m1 << std::endl;

}

void test_rows(){

  Matrix<int> m(4);
  std::cout << m.rows() << std::endl;

}

void test_cols(){

  Matrix<int> m(4);
  std::cout << m.cols() << std::endl;

}

void test_identity(size_t dim){

  Matrix<int> m_ident = identity<int>(dim);
  std::cout << m_ident <<std::endl;


}



int main(){

  test_Matrix();//Test both m and m(0)
  test_Matrix_dim();
  test_Matrix_row_col();
  test_Matrix_std_init_list();
  test_copy_constructor();
  test_move_constructor();
  test_move_assign_operator();

  test_rows();
  test_cols();



  test_mult_operator();
  test_plus_operator();
  test_minus_operator();

  test_mult_eq_operator();
  test_plus_eq_operator();
  test_minus_eq_operator();

  test_reset();
  test_insert_row();
  test_append_row();
  test_remove_row();
  test_insert_column();
  test_append_column();
  test_remove_column();

  test_identity(5);






}
