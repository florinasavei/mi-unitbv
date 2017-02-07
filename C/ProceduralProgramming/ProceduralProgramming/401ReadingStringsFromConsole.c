#include <stdio.h>

void main()
{
	char line[80];
	while (gets(line) != NULL)
		puts(line);
}