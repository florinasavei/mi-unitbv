%{#include<stdlib.h>
#include<string.h>
%}

%%
1*01*	printf("Cuvant care contine exact un 0 %s", yytext);

[^ \t\n]+	;
%%
int main()
{
	yylex();
	return 0;
}