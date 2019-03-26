int foo(){
  return 12;
}
int bar(){
  int res;
  int a = 7;
  {
    int b = 2;
    {
      int c = 1;
      {
        {
          int d = foo();
          res = a + b + c + d;
        }
      }
    }
  }
  return res;
}