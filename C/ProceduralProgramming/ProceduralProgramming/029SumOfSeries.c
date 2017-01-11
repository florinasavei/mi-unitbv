#include <stdio.h>

void main(){
	float x, y, t;
	int k;
	scanf_s("%f", &x);
	y = 0;
	t = 1; k = 1;

	while (t > 0){
		y = y + t;
		t = t*x/k;
		k++;
	}
	printf("%15.6f%15.6f\n", y, exp(x));
	getchar();

}