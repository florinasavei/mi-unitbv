%option noyywrap
%{
static FILE *f;
%}

/*
• Sa se elimine comentariile dintr-un fisier text ce conNine un program în limbajul C. 
*/

%%

\/\/.*	fprintf(f, "\n");

\/\*.*?\*\/	fprintf(f, "\n");

\/\*.*?		fprintf(f, "");
\*.*?		fprintf(f, "");
.*?\/\*		fprintf(f, "\n");



(.|\t|\n)	fprintf(f, "%s", yytext);

%%
int main(){
f = fopen("out.txt","w");

yylex();
fclose(f);
return 0;
}

\* *\