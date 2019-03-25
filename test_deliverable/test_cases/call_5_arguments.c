int global_variable = 5;
int bar(int a, int b, int c, int d, int e, int f, int g){
  return e;
}
int foo(){
  int x = bar(7, 2, 11, 12, 4, 5, 6);
  return x;
}
