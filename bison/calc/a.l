%{
#include "aparse.h"
extern int yylval;
%}

WS [ \t\n]
INT [1-9][0-9]*

%%

{WS} {}
"+" return(PLUS);
"-" return(MINUS);
"*" return(MUL);
"/" return(DIV);
"(" return(OB);
")" return(CB);
"%" return(MOD);
"!" return(NOT);
"|" return(OR);
"&" return(AND);
"~" return(COMP);
"^" return(XOR);
{INT} {
	yylval = atoi(yytext);
	printf("passing %d\n",yylval);
	return(NUM);
	}

%%






