int four(int a, int b, int c, int d){
	return d;
}

int five(int a, int b, int c, int d, int e){
	return e;
}

int six(int a, int b, int c, int d, int e, int f){
	return f;
}

int caller(){
	// int a = 1;
	// int b = 2;
	// int c = 3;
	// int d = 4;
	// int e = 5;
	// int f = 6;
	if ( four(1,2,3,4) < 4 ) {
		return 1;
	} else if ( five(1,2,3,4,5) < 5 ) {
		return 2;
	} else if ( six(1,2,3,4,5,6) < 6 ) {
		return 3;
	}
	return 0;
}