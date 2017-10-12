%{
	#include<stdio.h>
%}
%token OB CB
%token NUM
%token PLUS MINUS MUL DIV MOD
%token AND OR XOR
%token COMP NOT
%left  XOR AND OR
%left PLUS MINUS
%left DIV MUL MOD
%left COMP NOT
%start SS

%%

SS:
	EXPR {printf("result = %d\n", $1);}
	;

EXPR:
	OB EXPR CB {$$ = $2;} |
	EXPR PLUS EXPR {$$ = $1+$3;} |
	EXPR MINUS EXPR {$$ = $1-$3;} |
	MINUS EXPR {$$ = -$1;} |
	EXPR MUL EXPR {$$ = $1*$3;} |
	EXPR DIV EXPR {$$ = $1/$3;} |
	EXPR AND EXPR {$$ = $1&$3;} |
	EXPR OR EXPR {$$ = $1|$3;} |
	EXPR XOR EXPR {$$ = $1^$3;} |
	EXPR MOD EXPR {$$ = $1%$3;} |
	COMP EXPR {$$ = ~$2;} |
	NOT EXPR {$$ = !$2;} |
	NUM {$$ = $1;}
	;



%%

int main(void){
	yyparse();
}
