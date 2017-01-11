#include <stdio.h>

void main(){
	float a, sum, l;
	printf("enter numbers in rows, to end a row type zero, to end all row type double zero\n");
	do{
		l = sum = 0;
		do{
			scanf_s("%f", &a);
			if (a == 0) break;
			sum = sum + a;
			l++;
		} while (a); //exists first loop when zero is typed

		if (l) //lengths of the row is not null
			printf("\nsum of numbers on row= %f\n", sum);
	} while (l); //exits main loop when another zero is typed

	getchar();
}