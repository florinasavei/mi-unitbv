%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <math.h>
FILE *ff = fopen("iesire.txt", "wt");
%}
%%
\"[^"]* 	{if(yytext[yyleng-1]=='\\'){yymore();}else printf("sir = %s\n",yytext);}
%%
int main()
{
	yyin = fopen("intrare.txt", "rt");
	yylex();
	fclose(ff);
}