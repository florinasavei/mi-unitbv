%{
	#include<string.h>
	#include<ctype.h>
	#include<stdlib.h>

%}
%%
1*01* printf("\n cuvantul este=%s", yytext);
[^ \t\n]+ ;

%%
int main()
{
yylex();
return 0;
}