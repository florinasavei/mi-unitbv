%option noyywrap
%{
#include <stdio.h>
#include <string.h>
%}
%%
[0-1]+ 		{if(strstr(yytext,"011")==NULL)printf("%s\n",yytext);}
%%
int main()
{
yylex();
}