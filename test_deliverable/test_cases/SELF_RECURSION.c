int fun(int n){
	if (n){
		fun(n-1);
	} else {
		return n;
	}
}