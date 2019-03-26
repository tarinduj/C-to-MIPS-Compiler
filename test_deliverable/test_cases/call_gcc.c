extern int foo();
extern int foo_arg(int a, int b, int c, int d);
int bar(int a){
  return foo() + a + foo_arg(7, 3, 1, 9);
}