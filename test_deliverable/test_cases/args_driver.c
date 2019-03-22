int bar(int a, int b, int c, int d);
int main(){
  int res = 0;
  res += bar(1, 2, 3, 4);
  res += bar(0, 5, 7, 1);
  return res;
}