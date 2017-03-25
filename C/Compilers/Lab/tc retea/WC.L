/*
 *	word count, WC - the program. simple standalone PCLEX application.
 */

%{
static unsigned nchar = 0;	/* # of characters in file */
static unsigned nword = 0;	/* # of words in file */
static unsigned nline = 0;	/* # of lines in file */
%}

%%

\n              nchar += 2, ++nline;	/* line boundary in MS-DOS is CR LF */

[^ \t\n]+       ++nword, nchar += yyleng;

.               ++nchar;

%%

main()
{
  yylex();
  printf( "%d\t%d\t%d\n", nchar, nword, nline );
  exit(0);
}
