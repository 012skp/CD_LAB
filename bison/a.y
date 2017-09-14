%{
	#include<stdio.h>
%}


%token NUM
%token PLUS
%start SS


%%

SS:
	NUM PLUS fuck {$$ = $1+$3; printf("result = %d\n",$$);}
	;
fuck:	NUM {$$ = $1;} |
	NUM PLUS fuck {$$ = $1+$3;}
	;
%%

int main(void){
	yyparse();
}
