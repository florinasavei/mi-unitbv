%option noyywrap
%token DIGIT
%token ID
%token if
%token then
%token begin
%token end
%token procedure
%token function
%{
#include <stdio.h>
#include <math.h>
%}
DIGIT [0-9]
ID [a-z][a-z0-9]*
%%
if 	{return(IF);}
then 	{return(THEN);}
begin 	{return(BEGIN);}
end 	{return(END);}
procedure 	{return(PROCEDURE);}
function 	{return(FUNCTION);}
{DIGIT}+ 	{printf( "An integer: %s (%d)\n", yytext,atoi( yytext ) );}
{DIGIT}+("."{DIGIT}+)? 	{printf( "A float: %s (%g)\n", yytext,atof( yytext ) );}
if|then|begin|end|procedure|function 	{printf( "A keyword: %s\n", yytext );}
{ID} 	printf( "An identifier: %s\n", yytext );
"+"|"-"|"*"|"/" printf( "An operator: %s\n", yytext );
"{"[^}\n]*"}" /* eat up one-line comments BLOC DE INSTRUCTIUNI */
[ \t\n]+ /* eat up whitespace SPATII */
. printf( "Unrecognized character: %s\n", yytext );
%%
main(int argc,char** argv)
{
extern FILE *yyin;
if ( argc > 1 )yyin = fopen( argv[1], "r" );else yyin = stdin;
yylex();
/* Pot afisa undeva blocul de instructiuni in loc de BLOC DE INSTRUCTIUNI, le fel cu SPATII
Corectat parametrii:
-  tokenii mai sus si definirea celor scrisi cu litera mica
-  argc, argv, variabila yyin. cele de mai jos pot fi sau nu.
yydebug=1; errors=0; yyparse();
*/
}