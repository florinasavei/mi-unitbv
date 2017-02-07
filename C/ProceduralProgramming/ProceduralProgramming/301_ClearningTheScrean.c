// clearing the screan

#include <stdio.h>

void clear(){
	int i;
	for (i = 0; i < 24; i++)
		putchar('\n');
}

void main(){
	clear();
	printf("text now stars for here \n");
	getchar();
}