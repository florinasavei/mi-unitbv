%option noyywrap
%{
#include <stdio.h>
#include <string.h>
%}
%%
(1)*0(1)* 	{printf("%s\n",yytext);}
%%
int main()
{
yylex();
}