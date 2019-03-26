int unary_not();
int unary_tilde();
int unary_plus();
int unary_minus();

int main(){
	if (unary_plus() != 10) {
		return 1;
	}
	if (unary_minus() != -14) {
		return 2;
	}
	if (unary_not() != 0) {
		return 3;
	}
	if (unary_tilde() != -140) {
		return 4;
	}
	return 0;
}