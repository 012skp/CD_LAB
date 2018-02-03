%{
#include "aparse.h"
#include "meta_data.h"
%}

WS [ \t]
NUMBER ([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?)

%%

{WS} {}
"+" return(PLUS);
"-" return(MINUS);
"*" return(MUL);
"/" return(DIV);
"(" return(OB);
")" return(CB);
"!" return(NOT);
"|" return(OR);
"&" return(AND);
"^" return(XOR);
[\n] return(END); 
"#" return EOFF;

"true" {
	yylval.n = allocate();
	yylval.n->type = BVAL;
	yylval.n->bval = 1;
	yylval.n->dval = -124;
	printf("returning true with val = %d\n",yylval.n->bval);
	return NUM;
	}
"false" {
	yylval.n = allocate();
	yylval.n->type = BVAL;
	yylval.n->bval = 0;
	return NUM;
	}
{NUMBER} {
	yylval.n = allocate();
	yylval.n->type = DVAL;
	yylval.n->dval = atof(yytext);
	return(NUM);
	}
. {}
%%






