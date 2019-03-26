int odd(int sum, int b, int c, int d, int e, int f);

int even(int sum, int b, int c, int d, int e, int f){
	if(f==0){
		return sum;
	}
	else if(f % 2){
		sum++;
		return even(sum++,0,0,0,0,f-1);
	}
	else {
		sum++;
		return odd(sum++,0,0,0,0,f-1);
	}
}


int main(){
	return even(0,0,0,0,0,100) != 100;
}
