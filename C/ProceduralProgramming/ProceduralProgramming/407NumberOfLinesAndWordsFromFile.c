#include <stdio.h>
#include <string.h>

void main(int argc, char  *argv[])
{
	char line[200], *p, *sep = "\t\r\n";
	FILE *f;
	int nl = 0, nr = 0;

	if (argc < 2){
		printf(" The name of the file is missing \n");
		return;
	}

	if ((f = fopen(argv[1], "r")) == NULL){
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
}