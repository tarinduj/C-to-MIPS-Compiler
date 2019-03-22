int func1(int a, int b, int c, int d);
int func2(int d, int b, int a, int c);


int main()
{
	if (func1(1,2,3,4) != (1+2-3)*4)
		return 1;
	else if(func2(1,2,3,4) != (1+2-3)*4) 
		return 2;
	return 0;
}