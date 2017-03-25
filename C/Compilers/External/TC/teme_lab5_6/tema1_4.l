%option noyywrap
%{
#include <stdio.h>
#include <string.h>
%}
%%
[0-1]+ 		{int i,n=0; for(i=0;i<yyleng;i++)if(yytext[i]=='1')n++; if(n%2==0)printf("%s\n",yytext);}
%%
int main()
{
yylex();
}