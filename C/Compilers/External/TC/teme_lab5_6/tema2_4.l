%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <math.h>
FILE *ff = fopen("iesire.txt", "wt");
%}
%%
\/\/[^\n]* 	;
\/\*(^(\*\/))*\*\/ 	;
(.)*(^("\/\/"|"*/")) 		{printf("%s",yytext);}
%%
int main()
{
	yyin = fopen("intrare.txt", "rt");
	yylex();
	fclose(ff);
}