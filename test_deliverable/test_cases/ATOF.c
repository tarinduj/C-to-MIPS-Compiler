double atof(const char * string);
float fun(){
	char * buffer = "3.78125";
	float n = (float) atof (buffer);
	if ( n == 3.78125 ) {
		return 0;
	} else {
		return 1;
	}
}