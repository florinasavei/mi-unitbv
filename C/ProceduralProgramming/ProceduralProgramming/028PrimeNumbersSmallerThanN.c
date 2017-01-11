#include <stdio.h>

void main(){
	int n, m, d, np;

	printf("n=");
	scanf_s("%d", &n);
	if (n < 4){
		printf("\n%d\n", n); //first 3 numbers are prime anyway
		return;
	}


	np = 3; //there are at least 3 prime numbers;

	for (m = 5; m < n; m = m + 2){ //tries all the odd numbers
		for (d = 3; d < m; d = d + 2){ //tries all the possible deviders, also, testing even numbers would be redundant
				if (m%d == 0)
					break;
			}
			if (d >= m){
				printf("\nfound the prime numner : %d \n", m);
				np++;
		}	
	}
	printf("\nthere are %d prime numbers smaller than %d\n", np, n );
	getchar();
}