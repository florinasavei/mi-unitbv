%option noyywrap
%{

%}
/*Toate cuvintele care contin un număr par de 1 şi nici un 0  */

%%
(11)+	printf("cuvant acceptat:%s\n",yytext);
[^\t\n]+	;
.			;
%%

int main(){

yylex();

return 0;

}