int five = 5;
int ending; 
int result;

int func1(){
	result = 0;
	result = result + 5;
	result = five + result;
	int ten = five + five;
	result += ten;
	result += result;
	ending = 2;
	result += ending;
	ending = 7;
	return result;
}

int func2(){
	result = 0;
	result = result + 5;
	result = five + result;
	int ten = five + five;
	result += ten;
	result += result;
	result += ending;
	return result;
}
