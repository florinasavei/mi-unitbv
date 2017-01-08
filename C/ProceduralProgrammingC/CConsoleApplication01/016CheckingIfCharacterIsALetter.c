#include <stdio.h>

void main(){
	char ch;
	ch = getchar();
	if (ch >= 'a'&&ch <= 'z' || ch >= 'A'&&ch <= 'Z')
		printf("is a letter \n");
	else
		printf("is not a letter \n");
}