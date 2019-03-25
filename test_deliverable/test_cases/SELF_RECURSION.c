int fun(int n){
	if (n != 0){
		return fun(n-1);
	} else {
		return n;
	}
}