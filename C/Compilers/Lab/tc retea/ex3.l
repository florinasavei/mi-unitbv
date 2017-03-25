%{#include<stdlib.h>
#include<string.h>
#include<ctype.h>
%}
{subsir} 010
%%
[^subsir]	printf("cuvant care nu contine subsirul 010 %s", yytext);

[^ \t\n]+	;
%%
int main()
{
	yylex();
	
	return 0;
}