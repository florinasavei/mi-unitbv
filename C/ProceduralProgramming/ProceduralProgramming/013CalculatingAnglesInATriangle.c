#include <stdio.h>
#include <math.h>

void main(){
	float a, b, c, uab, ubc, uca;
	printf("Enter length of endged: ");
	scanf_s("%f%f%f", &a, &b, &c);
	uab = acos((b*b + c*c - a*b) / (2 * b*c));
	ubc = acos((b*b + a*a - c*c) / (2 * a*c));
	uca = acos((b*b + a*a - c*c) / (2 * a*b));
	printf("\n angle ab = %.2f \n angle bc = %.2f \n angle ca = %.2f \n sum of all angles = %.2f \n", uab, ubc, uca, uab+ubc+uca);
}