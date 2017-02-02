/* C program to implement DFA(Deterministic Finite Automata). */

#include<stdio.h> 
#include<conio.h> 
int main()
{
	FILE * fp;
	int Fa[10][10], states[2][10], row = 0, col = 0, sr = 0, sc = 0, flag = 0, i, j, in, curr;
	char k, *str;
	str = "";
	fp = fopen("AFD.txt", "r");
	if (fp == NULL)
		printf("file could not find\n");

	for (i = 0; i<3; i++)
	for (j = 0; j<10; j++)
		states[i][j] = -1;

	while (fscanf(fp, "%d", &in) != EOF)
	{
		fscanf(fp, "%c", &k);

		if (flag)
		{
			states[sr][sc++] = in;
			if (k == '\n')
			{
				sr++;
				sc = 0;
			}
		}
		else if (k == '#')
		{
			flag = 1;
			Fa[row][col++] = in;
		}
		else if (!flag)
		{
			Fa[row][col++] = in;
			if (k == '\n')
			{
				row++;
				col = 0;
			}
		}
	}

	printf("THE AUTOMATA IS : \n\n");
	for (i = 0; i <= row; i++)
	{
		for (j = 0; j<col; j++)
		{
			printf("%2d ", Fa[i][j]);
		}
		printf("\n");
	}

	printf("\n\nEnter the string : ");
	gets(str);
	curr = states[0][0];
	i = 0;
	while (str[i] != '\0')
	{
		curr = Fa[curr][str[i] - 97];
		if (curr == -1)
			break;
		i++;
	}

	flag = 0;
	if (curr != -1)
	{
		for (i = 0; i <= sc&&!flag; i++)
		{
			if (curr == states[1][i])
			{
				printf("\n\nSTRING ACCEPTED\n");
				flag = 1;
				break;
			}
		}
	}
	if (flag == 0)
		printf("\n\nSTRING NOT ACCEPTED ");
	 getchar();
	return 0;

}