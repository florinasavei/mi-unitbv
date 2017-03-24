%option noyywrap
%{
	/*Să se transforme toate secvenŃele de caractere albe într-un singur caracter alb şi
	secvenŃele de newline într-un singur newline dintr-un fişier text obŃinând rezultatul în alt
	fişier text.*/
	
	static FILE *f;
%}

%%
[ \t]+		fprintf(f," ");
[\n]+		fprintf(f," ");
[^ \t\n]	fprintf(f,yytext);
%%

int main(){

	f=fopen ("out.txt","w");
	yylex();
	fclose(f);
	return 0;
}