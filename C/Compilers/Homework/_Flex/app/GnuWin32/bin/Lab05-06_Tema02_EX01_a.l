%option noyywrap
%{
static FILE *f;
%}

/* Sa se transforme toate secvenNele de caractere albe 
 * �ntr-un singur caracter alb si secvenNele de newline �ntr-un 
 * singur newline dintr-un fisier text obNin�nd rezultatul �n alt fisier text. */

%%
[ \t]+ 	{fprintf(f," ");}
[\n]+ 	{fprintf(f," ");}
. 	{fprintf(f,"%s",yytext);}
%%
int main()
{
	f=fopen ("out.txt","w");
	yylex();
	fclose(f);
}