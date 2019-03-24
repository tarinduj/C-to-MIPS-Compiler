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
		ret = 1;
	else
		ret = odd(number-1);
	return ret;
  }