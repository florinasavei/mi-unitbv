#include <stdio.h>
#include <math.h>
void main(){
	float a, b, c, p, s;
	printf("Enter sides length:\n");
	scanf_s("%f%f%f", &a,&b,&c);
	p = (a + b + b) / 2;
	s = sqrt(p*(p - a)*(p - b)*(p - c));
	printf("\nArea is: %.2f \n", s);
	getchar();
}