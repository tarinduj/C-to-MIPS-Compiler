int global;

int func1(){
	global = 10;
	return 5;
}

int func2(){
	return global; 
}
