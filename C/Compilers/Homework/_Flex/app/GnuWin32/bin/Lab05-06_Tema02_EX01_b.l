%option noyywrap
%{
static FILE *f;
%}

/*Sa se determine toti identificatorii,
toate numerele �ntregi si toate
numerele reale dintr-un fisier text.  */
/* A lexical scanner generated by flex */


%%
[+-]?[1-9][0-9]*  	fprintf(f, "numar intreg: %s \n",yytext);
[+-]?[0-9]+\.[0-9]+	fprintf(f, "numar real: %s \n",yytext);
[A-Za-z][A-Za-z0-9_]*   fprintf(f, "identificator: %s \n",yytext);
%%

int main(){

f = fopen("out.txt","w");
yylex();
fclose(f);
return 0;
}