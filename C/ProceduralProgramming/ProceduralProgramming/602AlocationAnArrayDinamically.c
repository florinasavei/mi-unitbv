#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void main(){
	int n, i;
	int *a;
	printf("%d", sizeof(int));
	printf("n="); scanf_s("%f", &n);
	a = (int*)malloc(sizeof(int)*n);
	if (a == NULL)
	{
		printf("Allocation error\n");
		exit(1);
	}
	printf("enter the components of the array: \n");
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &a[i]);
	}
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("%d", a[i]);
	}
	free(a);
}