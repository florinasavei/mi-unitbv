%option noyywrap
%{
static FILE *f;
%}

/* Sa se transforme toate secvenNele de caractere albe 
 * într-un singur caracter alb si secvenNele de newline într-un 
 * singur newline dintr-un fisier text obNinând rezultatul în alt fisier text. */

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