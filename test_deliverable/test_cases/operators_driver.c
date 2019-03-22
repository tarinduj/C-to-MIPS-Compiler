int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);
int mod(int a, int b);
int shr(int a, int b);
int shl(int a, int b);
int band(int a, int b);
int bor(int a, int b);
int bxor(int a, int b);

int main()
{
	int y = 1998;
	int m = 6;
	if(add(y, m) != 2004)
		return 1;
	/*else if(sub(y, m) != 1992)
		return 2;
	*/else if(mul(y, m) != 11988)
		return mul(y,m);
	else if(div(y, m) != 333)
		return 4;
	else if(mod(y, m) != 0)
		return 5;
	else if(shr(y, m) != 127872)
		return 6;
	else if(shl(y, m) != 31)
		return 7;
	else if(band(y, m) != 6)
		return 8;
	else if(bor(y, m) != 1998)
		return 9;
	else if(bxor(y, m) != 1992)
		return 11;
	else 
		return 0;
}
