%option noyywrap
%{

%}

/*Toate cuvintele care nu conŃin subşirul 011*/

%%
[0-1]+ 		{if(strstr(yytext,"011")==NULL)printf("cuvant acceptat: %s\n",yytext);}
[^\t\n]+	;
.			;
%%

int main(){

yylex();

return 0;

}