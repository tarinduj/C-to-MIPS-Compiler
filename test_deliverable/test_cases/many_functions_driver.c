int func1();
int func2();

int main(int argc, char const *argv[])
{
	int res1 = func1();
	int res2 = func2();
	if (res1 == 5 && res2 == 10){
		return 0;
	} else {
		return 1;
	}
}