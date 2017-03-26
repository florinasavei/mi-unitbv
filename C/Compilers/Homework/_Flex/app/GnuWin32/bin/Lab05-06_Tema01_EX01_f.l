%option noyywrap
%{

%}
/*Toate cuvintele care nu contin subşirul 01  */

%%
[0-1]+ 		{if(strstr(yytext,"01")==NULL)printf("cuvant acceptat: %s\n",yytext);}
[^\t\n]+	;
.	;
%%

int main(){

yylex();

return 0;

}