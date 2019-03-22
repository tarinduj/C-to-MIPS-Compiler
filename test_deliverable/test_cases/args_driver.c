int foo(int x, int y);
int main(){
  int res = 0;
  res += foo(1, 0);
  res += foo(0, 1);
  res += foo(1, 1);
  res += foo(2, 1);
  res += foo(1, 2);
  res += foo(0, 0);
  return res != 10;
}