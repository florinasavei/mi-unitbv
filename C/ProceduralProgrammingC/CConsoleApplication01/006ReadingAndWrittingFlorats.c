#include <stdio.h>
void main(){
	float x;
	printf("x=");
	scanf_s("%f", &x);
	printf("you entered %f\n", x);
	getchar();
}