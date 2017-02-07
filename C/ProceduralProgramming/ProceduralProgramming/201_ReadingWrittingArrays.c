//reading and writting an array

#include< stdio.h>

int main(){
	int *a[100], n, i=0;
	printf("size of array n= ");
	scanf_s("%d", &n);
	printf("enter %d integers: \n", n);
	for (i = 0; i < n; i++)
		scanf_s("%d", &a[i]);
	for (i = 0; i < n; i++)
		printf("%d", a[i]);
	printf("\n");
	getchar();
	return 0;
}