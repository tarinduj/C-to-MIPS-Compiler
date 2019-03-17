int global_var;
int global_var2 = 5;
int functionDeclaration();

int foo()
{
  int x = 5, y = 7, b = 10;
  int z = x * y;
  int ab;
  int a, c;
  int d = z * (z - x) + x;
  a = z - x;
  c = 25 + z;
  return d;
}

int main()
{
  return global_var;
}

void voidfunction(){
  int y;
  global_var = y + global_var2;
}