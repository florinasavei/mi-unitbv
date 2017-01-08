#include <stdio.h>

void main(){
	int a, b, c, max;
	printf("enter 3 numbers one by one \n");
	scanf_s("%d%d%d", &a, &b, &c);
	max = a;
	if (max < b)
		max = b;
	if (max < c)
		max = c;

	printf("\nthe maximum is %d\n",max);
}