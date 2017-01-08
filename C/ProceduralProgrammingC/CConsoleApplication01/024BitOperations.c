//this will convert a number in binary

#include <stdio.h>

void main(){
	int n;
	printf("n=");
	scanf_s("%d", &n);
	unsigned int mask = 1 << 15; //bit 15 will be 1, the rest are 0
	while (mask){
		printf("%d", (mask & n) ? 1 : 0);
		mask >>= 1; //moving the mask to the right by one bit
	}
	printf("\n");
	getchar();
}