int foo(){
  int a = 6, b, c = 072, d;

  c += a; //c = 64
  b = a; //b = 6
  d = c + a + 5; //d = 75
  return d;
}