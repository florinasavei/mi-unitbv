%option noyywrap
%{

%}
/*Toate cuvintele care contin subşirul 01 */

%%
(0|1)*01(0|1)*	printf("cuvant acceptat:%s\n",yytext);
[^\t\n]+	;
.			;
%%

int main(){

yylex();

return 0;

}