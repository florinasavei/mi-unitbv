%option noyywrap
%{
	static FILE *f;
%}

%%
[ \t]+		fprintf(f," ");
[\n]+		fprintf(f," ");
[^ \t\n]	fprintf(f,yytext);
%%

int main(){

	f=fopen ("out.txt","w");
	yylex();
	fclose(f);
	return 0;
}