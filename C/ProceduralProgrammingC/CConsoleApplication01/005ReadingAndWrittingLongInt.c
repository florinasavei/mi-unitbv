#include <stdio.h>

void main(){
	long a;
	printf_s("a= ");
	scanf_s("%ld", &a);
	printf("you entered %ld\n", a);
	getchar();
}