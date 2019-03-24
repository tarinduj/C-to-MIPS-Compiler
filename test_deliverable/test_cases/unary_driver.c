#include <stdlib.h> 

int unary_plus();
int unary_minus();
int unary_not();
int unary_tilde();
int unary_address_of();


int main()
{
	if (unary_plus() != 42) {
		return 1;
	} else if (unary_minus() != -47) {
		return 2;
	} else if (unary_not() != 0) {
		return 3;
	} else if (unary_tilde() != -70) {
		return 4;
	} else if (unary_address_of() && 0) {
		return 5;
	}
	return 0;
}