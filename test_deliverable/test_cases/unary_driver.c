int unary_plus();
int unary_minus();
int unary_not();
int unary_tilde();

int main(){
	if (unary_plus() != 42) {
		return 1;
	} 
	if (unary_minus() != 15) {
		return 2;
	} 
	if (unary_not() != 0) {
		return 3;
	} 
	if (unary_tilde() != -70) {
		return 4;
	}
	return 0;
}