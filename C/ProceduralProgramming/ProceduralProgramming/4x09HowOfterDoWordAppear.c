///Program pentru citirea unui text sursa C in memorie si afisarea frecventei de aparitie a urmatoarelor cuvinte cheie in text: if, for, do, while, whitch, break

#include <stdio.h>
#include <string.h>

int keyw(char *nume, char *kw[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (strcmp(nume, kw[i]) == 0)
			return i;
		return -1;
}

char *next(char *adr, char *rez)
{
	while (*adr && !isalpha(*adr))
		++adr;
	while (*adr && isalpha(*adr))
		*rez++ = *adr++;
	*rez = 0;

	if (*adr == 0)
		return 0;
	else
		return adr;
}

void main()
{
	FILE *f; char buf[128];
	char *p, *r, w[20];
	char *kw[5] = { "do", "for", "if", "while", "break" };
	int nr[5] = { 0 };
	int k, lc, n = 5;

	printf("nume fisier:"); scanf("%s", buf);

	f = fopen(buf, "r");

	if (f == NULL){ printf("Fisierul %s nu exista \n", buf); return; }

	while (fgets(buf, 128, f) != 0)
	{
		p = buf;
		while (r = next(p, w))
		{
			printf("%s", w);
			k = keyw(w, kw, n);
			if (k > 0)
				nr[k]++;
			p = r;
		}
	}
	getchar();
	getchar();
}