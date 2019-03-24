int func1(int a, int b, int c, int d, int e);
int func2(int d, int b, int a, int c, int e);


int main()
{
	if (func1(5,2,3,4,2) != ((5+2-3)*4)/2)
		return 1;
	else if(func2(5,2,3,4,2) != ((5+2-3)*4)/2) 
		return 2;
	return 0;
}