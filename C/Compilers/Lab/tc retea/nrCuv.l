%{
	int nrChar=0, nrCuv=0,nrLines=0;
%}

%%
[^ \t\n]	nrCuv++;
.		nrChar++;
\n		{nrLines++;nrChar+=2;}
%%

void main()
{
	yylex();
	printf("nrCuv=%d, nrChar=%d, nrLines=%d\n",nrCuv, nrChar,nrLines);
}