#include <stdio.h>

void main(){
	int a, b, r;
	printf("a,b: \n");
	scanf("%d%d", &a, &b);
	while (r = a%b){
		a = b;
		b = r;
	}
	printf("\ncmmdc=%d\n", b);
	getchar();
}