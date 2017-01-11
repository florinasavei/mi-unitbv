#include <stdio.h>
void main(){
	int a, b, r;
	printf("a,b: \n");
	scanf("%d%d", &a, &b);
	if (a%b == 0){
		printf("\ncmmdc=%d\n", b);
		return;
	}
	if (b%a == 0){
		printf("\ncmmdc=%d\n", a);
		return;
	}
	do{
		r = a%b;
		a = b;
		b = r;
	} while (r);
	printf("\cmmdc=%d\n", a);
	getchar();
}