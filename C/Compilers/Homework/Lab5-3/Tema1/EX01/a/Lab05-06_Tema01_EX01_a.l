%option noyywrap
%{

%}
/*Toate cuvintele care se termina in 01*/

%%
(0|1)*01	printf("cuvant acceptat:%s\n",yytext);
[^\t\n]+	;
.			;
%%

int main(){

yylex();

return 0;

}