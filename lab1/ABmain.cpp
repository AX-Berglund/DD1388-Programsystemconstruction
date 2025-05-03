
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
