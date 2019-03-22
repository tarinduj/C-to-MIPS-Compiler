int fib(int);

int main()
{
	if(fib(0) != 0){
		return -1;
	} else if (fib(1) != 1){
		return 1;
	} else if (fib(2) != 1){
		return 2;
	} else if (fib(3) != 2){
		return 3;
	} else if (fib(5) != 5){
		return 5;
	} else if (fib(10) != 55){
		return 10;
	}
	else if (fib(23) != 28657){
		return 23;
	}
	return 0;
}