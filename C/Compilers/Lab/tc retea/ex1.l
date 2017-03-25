%{#include<stdlib.h>
#include<string.h>
%}
%%
(0|1)*01	printf("Cuvant care se termina cu 01 ", yytext);
1*01*	printf("Cuvant care contine exact un 0 ", yytext);
(11)*	printf("Cuvant care contine numar par de 1 si niciun 0 ", yytext);
(11)*0*(11)*	printf("Cuvant care contine un numar par de 1 ", yytext);
(0|1)*01(0|1)*	printf("Cuvant care contine subsirul 01 ", yytext);
^(010)	printf("Cuvant care nu contine subsirul 010 ", yytext);
%%
void main()
{
	yylex();
}