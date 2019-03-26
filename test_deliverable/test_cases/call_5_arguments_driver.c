/*#include <stdio.h>*/

int call_get_a();
int call_get_b();
int call_get_c();
int call_get_d();
int call_get_e();
int call_get_f();
int call_get_g();

int main(){
 	/*printf("Arguments got back in order: %d %d %d %d %d %d %d. ", call_get_a(), call_get_b(), call_get_c(), call_get_d(), call_get_e(), call_get_f(), call_get_g()); */
 	if(call_get_a() != 1){
		return 1;
	} 
	else if(call_get_b() != 2){
		return 2;
	} 
	else if(call_get_c() != 3){
		return 3;
	} 
	else if(call_get_d() != 4){
		return 4;
	} 
	else if(call_get_e() != 5){
		return 5;
	} 
	else if(call_get_f() != 6){
		return 6;
	} 
	else if(call_get_g() != 7){
		return 7;
	} else {
		return 0;
	}
}