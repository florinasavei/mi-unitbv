&{
	#include<string.h>
	#include<ctype.h>
	#include<stdlib.h>

static unsigned nrNum = 0;

%}
%%

.[01]$		nrNum++;
%%
void main()
{
yylex();
printf("\n",nrNum);
}