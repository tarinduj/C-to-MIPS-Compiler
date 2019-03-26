int if2(){
  int x = 7;
  int y = 0;
  int z = 2;
  if(x){
    x += 4;
    z += 1;
  } 
  if(z) {
    if(y){
      y += 1;
    }
    else if(z){
      x += z;
    }
    else {
      x += 4;
    }
  }
  return x + y;
}