#include<stdio.h>

void main(){
	int a = 7, b = 2;
	printf("a=%d b=%d c=%d r=%d\n", a, b, a/b, a%b);
	printf("a=%d b=%d c=%d r=%d\n", -a, b, -a/b, -a%b);
	printf("a=%d b=%d c=%d r=%d\n", a, -b, a/-b, a%-b);
	printf("a=%d b=%d c=%d r=%d\n", -a, -b, -a/-b, -a%-b);
	getchar();
}