int odd(int number){
	int ret;
	if (number==0) 
		ret = 0;
	else
		ret = even(number-1);
	return ret;
}
int even(int number){
	int ret;
	if(number==0) 
		return 1;
	else{
		return odd(number-1);
  }
}
