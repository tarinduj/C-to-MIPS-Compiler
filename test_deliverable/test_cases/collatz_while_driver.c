int collatz(int);

int main()
{
	if(collatz(21) != 7){
		return 1;
	} else if (collatz(3) != 7){
		return 2;
	} else if(collatz(80) != 9){
		return 3;
	} else if(collatz(52) != 11){
		return 4;
	} else if (collatz(7) != 16){
		return 5;
	} else if (collatz(1) != 0){
		return 6;
	} else if (collatz(2) != 1){
		return 7;
	}
	return 0;
}