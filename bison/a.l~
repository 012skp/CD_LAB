%{
#include "a.tab.h"
extern int yylval;
%}

WS [ \t\n]
INT [1-9][0-9]*

%%

{WS} {}
"+" return(PLUS);
{INT} 	{
	yylval = atoi(yytext);
	return(NUM);
	}
%%



