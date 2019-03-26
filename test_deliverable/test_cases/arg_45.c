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

	int fo = four(1,2,3,4);
	int fo2 = four(1,2,3,4);
	int fi = five(1,2,3,4,5);
	int fi2 = five(1,2,3,4,5);
	int si = six(1,2,3,4,5,6);
	int si2 = six(1,2,3,4,5,6);
	if(fo != 4 && fi != 5 && si != 6 && fo2 != 4 && fi2 != 5 && si2 != 6){
		return 1;
	} else {
		return six(1,2,3,4,5,6);
	}
}
