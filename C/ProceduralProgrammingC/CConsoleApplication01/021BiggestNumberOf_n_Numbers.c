#include <stdio.h>
#include <limits.h>

void main(){
	int n, i, a, amax;
	printf("number of numbers= ");
	scanf_s("%d", &n);
	amax = INT_MIN; //smallest integer number
	printf("\nenter %d numbers:\n",n);
	for (i = 0; i < n; i++){
		scanf_s("%d", &a);
		if (amax < a)
			amax = a;
	}
	printf("\nbiggest numbers is %d \n", amax);
	getchar();
}