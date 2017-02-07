#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <process.h>
#include <malloc.h>

void EroareAloc()
{
	printf("Eroare! Memorie insuficienta");
	exit(1);
}

float **MatrAlloc(int m, int n){
	int i;
	float **a;
	if ((a = (float**)calloc(m, sizeof(float*))) == NULL) EroareAloc();

	for (i = 0; i < m; i++)
	{
		if ((a[i] = (float*)calloc(n, sizeof(float))) == NULL) EroareAloc();
	}
}

void main(){
	char numef[100];
	int i, j, k, m, n, n2, p;
	float **a, **b, **c, f;
	FILE *fis;

	printf("Dati numele fisierului text cu prima matrice:");
	gets(numef);
	//numef="";
	fis = fopen(numef, "rt");
	if (fis == NULL){ printf("Eroare, nu s-a outut deschide fisierul %s !\n", numef); getchar(); exit(0); }
	fscanf(fis, "%d%d", &m, &n);
	a = MatrAlloc(m, n);

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			fscanf(fis, "%f%", &f);
			a[i][j] = f;
			printf("%10.2lf", a[i][j]);
		}
		puts("");
	}
	fclose(fis);

	printf("Datii numele fisierului cu a adoua matrice ");
	gets(numef);
	fis = fopen(numef, "rt");
	//numef=
	if (fis == NULL){ printf("Eroare, nu s-a outut deschide fisierul %s !\n", numef); getchar(); exit(0); }
	
	fscanf(fis, "%d%d", &n2, &p);
	if (n != n2)
	{
		fclose(fis);
		printf("Eroare! Mtricile nu se pot inmultiL \n");
		printf("A(%d,%d)xB(%d,%d)\n", n, m, n, p);
		getchar(); exit(0);
	}
	b = MatrAlloc(n2, p);
	for (i = 0; i < n2; i++)
	{
		for (j = 0; j < p; j++)
		{
			fscanf(fis, "%f", &f);
			b[i][j] = f;
			printf("%10.2lf", b[i][j]);
		}
	}
	fclose(fis);

	printf("Dati numele fisierului in care sa se puna rezultatul: ");
	gets(numef);
	if (fis == NULL){ printf("Eroare, nu s-a putu deschide fisierul %s !\n", numef); getchar(); exit(0); }
	fis = fopen(numef, "wt");
	c = MatrAlloc(m, p);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < p; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < n; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < p; j++)
		{
			printf("%10.2f", c[i][j]);
			fprintf(fis, "10.2f", c[i][j]);
		}
		printf("\r\n");
		fprintf(fis, "\r\n");
	}

	for (i = 1; i < m; i++) free(a[i]); free(a);
	for (i = 1; i < n; i++) free(b[i]); free(b);
	for (i = 1; i < m; i++) free(c[i]); free(c);
	fclose(fis);
	getchar();
	getchar();
	
}