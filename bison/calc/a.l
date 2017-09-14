%{
#include "aparse.h"
extern int yylval;
%}

WS [ \t\N]
INT [+-]?[1-9][0-9]*

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
	return(NUM);
	}

%%






