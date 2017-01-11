#include <stdio.h>

void main(){
	int a, b, d;
	printf("a,b: \n");
	scanf("%d%d", &a, &b);
	d = a < b ? a : b; //d =min(a,b);
	while (a%d || b%d)
		d = d - 1;
	printf("\ncmmdc=%d\n",d);
	getchar();
}