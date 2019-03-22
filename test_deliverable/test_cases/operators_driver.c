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
int assign_add(int , int);
int assign_sub(int , int);
int assign_mul(int , int);
int assign_div(int , int);
int assign_mod(int , int);
int assign_shr(int , int);
int assign_shl(int , int);
int assign_band(int , int);
int assign_bor(int , int);
int assign_bxor(int , int);

int main()
{
	int y = 1998;
	int m = 6;
	if(add(y, m) != 2004)
		return 1;
	else if(sub(y, m) != 1992)
		return 2;
	else if(mul(y, m) != 11988)
		return 3;
	else if(div(y, m) != 333)
		return 4;
	else if(mod(y, m) != 0)
		return 5;
	else if(shr(y, m) != 31)
		return 6;
	else if(shl(y, m) != 127872)
		return 7;
	else if(band(y, m) != 6)
		return 8;
	else if(bor(y, m) != 1998)
		return 9;
	else if(bxor(y, m) != 1992)
		return 11;
	else if(assign_add(y, m) != 2004)
		return 12;
	else if(assign_sub(y, m) != 1992)
		return 13;
	else if(assign_mul(y, m) != 11988)
		return 14;
	else if(assign_div(y, m) != 333)
		return 15;
	else if(assign_mod(y, m) != 0)
		return 16;
	else if(assign_shr(y, m) != 31)
		return 17;
	else if(assign_shl(y, m) != 127872)
		return 18;
	else if(assign_band(y, m) != 6)
		return 19;
	else if(assign_bor(y, m) != 1998)
		return 20;
	else if(assign_bxor(y, m) != 1992)
		return 21;
	else 
		return 0;
}
