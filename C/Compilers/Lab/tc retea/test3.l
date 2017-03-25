
%%
[01]*01	printf("\n bun=%s",yytext);
[01]*		;

%%
int main()
{
	yylex();
	return 0;
}