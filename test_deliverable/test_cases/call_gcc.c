int foo();
int foo_arg(int a, int b, int c, int d);
int bar(int a){
  /*int res = foo_arg(7,3,1,9);*/
  return  a + foo_arg(7,3,1,9) + foo();
}