%option noyywrap
%{

%}
/*Toate cuvintele care conŃin un număr par de 1*/

%%
(0*10*10*)*	printf("cuvant acceptat:%s\n",yytext);
[^\t\n]+	;
.			;
%%

int main(){

yylex();

return 0;

}