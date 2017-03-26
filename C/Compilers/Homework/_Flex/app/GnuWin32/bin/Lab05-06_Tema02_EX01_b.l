%option noyywrap
%{

%}

/*Sa se determine toNi identificatorii, 
toate numerele întregi si toate 
numerele reale dintr-un fisier text.  */

%%

%% 
_?[a-zA-Z_][a-zA-Z0-9_]+ 	{printf("identificator: %s\n",yytext);}
[-+]?[0-9]+ 		{printf("intreg: %s\n",yytext); return atoi(yytext);}
[-+]?[0-9]+(\.[0-9]+)? 	{printf("real - intreg: %s\n",yytext); return atof(yytext);}
%%

%%
int main()
{

	yylex();
	fclose(f);
}