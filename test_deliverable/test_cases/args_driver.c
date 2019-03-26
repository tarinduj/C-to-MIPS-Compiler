int bar(int a, int b, int c, int d);
int main(){
  int res = 0;
  if(bar(1, 2, 3, 4) != 252){
  	return 1;
  } else if (bar(0, 5, 7, 1) != 235) {
  	return 2;
  }
  return 0;
}