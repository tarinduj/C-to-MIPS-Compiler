int fib(int n){
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else {
		int res = fib(n-1);
		res += fib(n-2);
		return res;
	}
}