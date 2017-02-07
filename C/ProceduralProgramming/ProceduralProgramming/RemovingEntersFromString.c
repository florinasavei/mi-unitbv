#include <stdio.h>
#include <string.h>

void main()
{
	char linie[80];
	char text[3000] = { 0 };
	while (gets(linie) != NULL)
	{
		strcat(linie, "\b");
		strcat(text, linie);
	}
	puts(text);
}