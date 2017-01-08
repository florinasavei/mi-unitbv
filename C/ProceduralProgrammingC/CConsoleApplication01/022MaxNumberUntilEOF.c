#include <stdio.h>
void main(){
	int a, sum;
	sum = 0;
	printf("\nTo stop this program press CTRL+Z\n");
	while (scanf("%d", &a) != EOF)
	sum = sum + a;
	printf("\nSUM = %d\n", sum);
	getchar();
}