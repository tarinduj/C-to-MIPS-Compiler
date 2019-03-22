/*int foo(int x, int y){
  int res = 0;
  if(x && y){
    res += 1;
  }
  if(x || y){
    res += 1;
  }
  if(x == y){
    res += 1;
  }
  return res;
}*/

int bar(int a, int b, int c, int d){
  int res = a;
  res += 5 + (a*a);
  res *= 2 * a;
  res -= 67;
  res >>= a + 1;
  res &= 0xFF|a;
  return res + a + b + c + d;
}
