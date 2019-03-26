int size(){
  int x = 5;
  int y = sizeof(int);
  if(sizeof(x) == 4 && y == 4){
    return 4;
  } else {
    return 6;
  }
}