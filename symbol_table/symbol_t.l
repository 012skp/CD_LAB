%{
#include "symbol_ty.h"
#include "ch3hdr.h"
#include <math.h>
%}

%%
([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
		yylval.dval = atof(yytext);
		return NUMBER;
	}
[ \t] {
		/* ignore whitespaces */
	}
[A-Za-z][A-Za-z0-9]* {
		yylval.symp = symlook(yytext);
		return NAME;
	}
"$"	{
		return 0;
	}
\n 	| 
. 	{
		return yytext[0];
	}
%%
