%option noyywrap
%{
static FILE *f;
%}

/*

Sa se determine sirurile de caractere dintr-un fisier text ce conNine un program în limbajul C. 

*/

%%

[A-Za-z][A-Za-z0-9_]*   fprintf(f, ": %s \n",yytext);
%%
int main(){

f = fopen("out.txt","w");
yylex();
fclose(f);
return 0;
}