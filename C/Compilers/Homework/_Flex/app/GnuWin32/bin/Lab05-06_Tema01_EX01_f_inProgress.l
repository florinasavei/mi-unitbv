%option noyywrap
%{

%}
/*Toate cuvintele care nu conŃin subşirul 01  */

%%
(0*0*10*)*	printf("cuvant acceptat:%s\n",yytext);
[^\t\n]+	;
.			;
%%

int main(){

yylex();

return 0;

}