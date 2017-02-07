#include <stdio.h>
#include <malloc.h>

void main(){
	int i, j, m, n;
	float **a;

	printf("Enter the size of the matrix");
	scanf_s("%d%d", &m, &n);
	a = (float**)calloc(m, sizeof(float*));
	if (a == NULL)
	{
		printf("Not enought memory");
		exit(1);
	}

	for (i = 0; i < m; i++)
	{
		a[i] = (float*)calloc(n, sizeof(int));
		if (a[i] == NULL)
		{
			printf("Not enough moemory");
			exit(1);
		}
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("Enter A[%d,%d]= ", i+1, j+1);
			scanf("%d", &a[i][j]);
		}
	}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}

	getchar();

	///free memory
	for (i = 0; i < m; i++)
	{
		free(a[i]);
	}
	free(a);

	getchar();
	getchar();
	getchar();
}