%{
#include <stdio.h>

static FILE *rez;
%}

spatii_albe	[ \t]+
linii_noi	[\n]+

%%

^{spatii_albe}		;
{spatii_albe}		fprintf(rez," ");
{linii_noi}		fprintf(rez,"\n");
.			fprintf(rez,yytext);
%%
void main( )
{
	if(rez=fopen("text.txt","w"))
		yylex();
	else printf("eroare la deschidere de fisier");
}
