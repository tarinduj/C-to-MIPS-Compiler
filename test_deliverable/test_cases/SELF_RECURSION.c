int fun(int n){
	if (n){
		return fun(n-1);
	} else {
		return n;
	}
}