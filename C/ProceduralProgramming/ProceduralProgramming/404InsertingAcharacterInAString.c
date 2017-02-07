#include <stdio.h>
#include <string.h>

void Chins (char *d, char ch)
{
	char *p;
	for (p = d + strlen(d); p >= d; p--)
		*(p + 1) = *p;
	*d = ch;
}

void main()
{
	char *s="Mimi";
	char c = "lolo";
	Chins(s,c);

}