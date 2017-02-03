///displaying pointers in hexa

# include <stdio.h>

void main(){
	float f;
	char *p; int i;

	for (f = 0; f < 10; f=f + 0.5){
		printf("%6.2f\t", f);
		p = (char*)&f;//the address of the first bit
		for (i = 0; i < sizeof(f);i++)
			printf("%f02x ", *p++);
		printf("\n");
	}
	getchar();
}