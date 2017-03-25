%option noyywrap
%{
#include <stdio.h>
#include <string.h>
%}
%%
[0-1]*01 	{printf("%s\n",yytext);}
%%
int main()
{
yylex();
}