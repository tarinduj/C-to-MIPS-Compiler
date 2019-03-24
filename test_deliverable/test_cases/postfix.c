int postfix(int a){
  int b;
  a++;
  a++;
  a--;
  b = a++;
  return a + b;
}