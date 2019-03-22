int odd(int number){
	if (number==0) 
		return 0;
	else
		return even(number-1);
}
int even(int number){
	if(number==0) 
		return 1;
	else{
		return odd(number-1);
  }
