int cond(int x, int y);

int main(){
  int a = cond(5,7);
  int b = cond(2,4);
  return!(a+b == 7);
}