// int g_var = 5;
// int g_var2 = 99;
// int testIF(int x, int y){
//   int l_var;
//   int l_var2 = 6;
//   if(x && y){
//     return 22;
//   }
//   if(x)
//     y = 7;
//   else {
//     if((y == 2) || x == 99)return y;
//     else{
//       y = 22&x;
//     }
//   }
//   return y;
// }

// int testWHILE(int a, int c, int d){
//   while(a>5){
//     int b = 7;
//     a = a - b;
//     testIF(a, testWHILE(a,b,c));
//   }
//   return testIF(a, 0);
// }

// int main(){
//   return f(5);
// }

// int f(int x)
// {
//   int a = 6 * 35;
//   if(x>1){
//     return x*f(x-1);
//   }else{
//     return x;
//   }
// }

// void voidggg(){
// return;
// }

// int main()
// {
//     return eliftest(2);
// }

// int eliftest(int x){
//   if(x == 1){
//     x = 69;
//     return 7;
//   } 
//   else if(x == 2){
//     if(x < 3) return x;
//     else if(x > 1 ) return x + 1;
//     else return 44;
//   } 
//   else if(x == 5){
//     return x + 5;
//   }
//   else{
//     x = 1488;
//     return 9;
//   } 
//   if(x){}
//   else{
//     return 5;
//   }
// }

int foo(int x, int y){
  x += 1;
  return x + y;
}
