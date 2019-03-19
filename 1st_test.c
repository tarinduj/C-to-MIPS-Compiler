int g_var1 = 7;
int g_var2 = 69;

int testARG(int x, int y){
  int a = (x-(g_var1))*y*(y*y);
    int z = 8;
int c = a + z;
  return c*(x +y)/g_var2;
}

int testFUNCTIONCALL(){
  return foo(3, 7);
}

int g_var3 = 5;
int testIF(int x, int y){
    if(x) y = 7 + g_var3;
    else y = 2 - g_var3;
    return y;
}