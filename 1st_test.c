int g_var = 5;
int testIF(int x, int y){
  int l_var;
  int l_var2 = 6;
  if(y){
    return 22;
  }
  if(x)
    y = 7;
  else {
    if(y == 2)return y;
    else{
      y = 22;
    }
  }
  return y;
}