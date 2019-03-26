int unary(int a){
  int b = ++a;
  int c = --a;
  ++a;
  return a + b + c;
}