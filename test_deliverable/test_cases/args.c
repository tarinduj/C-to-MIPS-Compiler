int foo(int x, int y){
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
}
