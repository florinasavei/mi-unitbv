#include <stdio.h>
#include <string.h>

void main(int argc, char  *argv[])
{
	char line[200], *p, *sep = " ", filename[50];
	FILE *f;
	int nl = 0, nr = 0;

	puts("enter filename");
	gets(filename);

	if ((f = fopen(filename, "r")) == NULL){
		printf("file not found \n");
		return;
	}

	while (fgets(line, 200, f) != NULL){
		nl++;
		p = line;
		while ((p = strtok(p, sep)) != NULL)
		{
			++nr;
			p = p + strlen(p) + 1;
		}
	}
	printf("\n %d lines %d words", nl, nr);
	fclose(f);

	getchar();
	getchar();
}