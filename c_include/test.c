#include <stdio.h>
int main(){
	int a = 1;
	#include "test.h"
	printf("in test.c a = %d\n", a);
	return 0;
}