//calculating distance and sloap between two points
#include <stdio.h>
#include <math.h>
#include <limits.h>

void main(){
	float x1, y1, x2, y2, d, u;
	printf("x1,y1:\n");
	scanf_s("%f%f", &x1, &y1);
	printf("x2,y2:\n");
	scanf_s("%f%f", &x2, &y2);
	d = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	if (x2 != x1)
		u = atan((y2 - y1) / (x2 - x1));
	else
		u = LLONG_MAX; //verticle(infinite sloap)
	printf("\ndistance: %.2f sloap:%.2f\n", d, u);
	getchar();
}