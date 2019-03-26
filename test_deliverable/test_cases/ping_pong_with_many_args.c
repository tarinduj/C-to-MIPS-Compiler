int even(int sum, int b, int c, int d, int e, int f);

int odd(int sum, int b, int c, int d, int e, int f){
	int x; /*dummy unused variables*/
	int y;
	int z;
	if(f==0){
		return sum;
	}
	else if(!(f % 2)){
		return even(++sum,0,0,0,0,f-1);
	}
	else {
		return odd(++sum,0,0,0,0,f-1);
	}
}