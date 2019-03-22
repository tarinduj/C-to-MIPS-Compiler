int nested_while(int a){
  int b = 10;
  while(a <= 6){
    while(b > 3){
      a += 1;
      b -= 1;
    }
  }
  return a + b;
}