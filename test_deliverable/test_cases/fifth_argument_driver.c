int fifth(int a1, int a2, int a3, int a4, int a5, int a6);
int sixth(int a1, int a2, int a3, int a4, int a5, int a6);
int main(int argc, char const *argv[])

{
	if(fifth(1,2,3,4,5,6) != 5){
		return 5;
	} else if (sixth(1,2,3,4,5,6) != 6){
		return 6;
	}
	return 0;
}