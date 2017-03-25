%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <math.h>
FILE *ff = fopen("iesire.txt", "wt");
%}
%%
_?[a-zA-Z_][a-zA-Z0-9_]+ 	{printf("identificator: %s\n",yytext);}
[-+]?[0-9]+ 		{printf("intreg: %s\n",yytext); return atoi(yytext);}
[-+]?[0-9]+(\.[0-9]+)? 	{printf("real - intreg: %s\n",yytext); return atof(yytext);}
%%
int main()
{
	yyin = fopen("intrare.txt", "rt");
	yylex();
	fclose(ff);
}