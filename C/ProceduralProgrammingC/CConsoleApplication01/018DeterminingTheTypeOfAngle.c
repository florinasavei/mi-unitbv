#include <stdio.h>

void main(){
	int a, b, c;
	printf("eter the endges of the triangle: \n");
	scanf_s("%d%d%d",&a,&b,&c);
	if ((a < b + c) && (b < a + c) && (c < a + b))
	if ((a == b) && (b == c))
		printf("\nequilateral\n");
	else
	if ((a == b) || (a == c) || (b == c))
		printf("\nisosceles\n");
	else
		printf("\nregular triangle\n");
	else printf("\nimpossible\n");
	getchar();
}