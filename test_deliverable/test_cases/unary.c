int unary_plus(){
	return +42;
}
int unary_minus(){
	int a = 47;
	int b = 0 - a;
	int c = -47;
	if(b == c){
		return 15;
	}
	return 55;
}

int unary_not(){
	return !47;
}

int unary_tilde(){
	return ~69;
}
