#include <stdlib.h>

float fun(){
	char * buffer = "3.78125";
	float n = atof (buffer);
	if ( n == 3.78125 ) {
		return 0;
	} else {
		return 1;
	}
}