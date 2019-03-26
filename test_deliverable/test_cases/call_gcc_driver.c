int bar(int a);
int foo(){
  return 12;
}
int foo_arg(int a, int b, int c, int d){
  return a + b + c + d;
}
int main(){
  return !(bar(4) == 36);
}