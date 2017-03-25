%option noyywrap
%{
#include <stdio.h>
#include <string.h>
%}
%%
[1]+ 		{if(yyleng%2==0)printf("%s\n",yytext);}
%%
int main()
{
yylex();
}