%option noyywrap
%{
#include <stdio.h>
#include <string.h>
%}
%%
[0-1]+ 		{if(strstr(yytext,"01")==NULL)printf("%s\n",yytext);}
%%
int main()
{
yylex();
}