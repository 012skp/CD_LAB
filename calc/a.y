%{
	#include<stdio.h>
	#include "meta_data.h"
%}



%union {
	struct node *n;
}

%token END 
%token OB CB
%token <n> NUM
%token PLUS MINUS MUL DIV EOFF
%token AND OR XOR
%token NOT
%left  XOR AND OR
%left PLUS MINUS
%left DIV MUL 
%right NOT
%start SS

%type <n> EXPR

%%

SS:
	E SS |
	END SS |
	EOFF {printf("fuck over\n"); return 0;} 
	;

E:
	EXPR END {
			if($1->type == DVAL) printf("result = %lf\n", $1->dval);
			else printf("result = %s\n",($1->bval==1)?"true":"false");
		}	
	;

EXPR:
	OB EXPR CB {$$ = $2;} |
	EXPR PLUS EXPR {$$->type = DVAL;
			double a = ($1->type == DVAL)?$1->dval:(double)$1->bval;
			double b = ($3->type == DVAL)?$3->dval:(double)$3->bval;
			if($3->type == BVAL) printf("second arg is BVAL with val = %lf\n",(double)$3->bval);
			if($3->type == DVAL) printf("second arg is DVAL with val = %lf\n",(double)$3->dval);
			if($1->type == BVAL) printf("first arg is BVAL with val = %lf\n",(double)$1->bval);
			if($1->type == DVAL) printf("first arg is DVAL with val = %lf\n",(double)$1->dval);
			$$->dval = a+b;
			printf("%lf + %lf = %lf\n",a,(double)$3->bval,$$->dval);	
			} 
			|
	EXPR MINUS EXPR {$$->type = DVAL;
			double a = ($1->type == DVAL)?$1->dval:(double)$1->bval;
			double b = ($3->type == DVAL)?$3->dval:(double)$3->bval;
			$$->dval = a-b;		
			} 
			|
	MINUS EXPR     {$$->type = DVAL;
			double a = ($2->type == DVAL)?$2->dval:(double)$2->bval;
			$$->dval = -a;		
			} 
			|
	EXPR MUL EXPR  {$$->type = DVAL;
			double a = ($1->type == DVAL)?$1->dval:(double)$1->bval;
			double b = ($3->type == DVAL)?$3->dval:(double)$3->bval;
			$$->dval = a*b;		
			} 
			|
	EXPR DIV EXPR  {$$->type = DVAL;
			double a = ($1->type == DVAL)?$1->dval:(double)$1->bval;
			double b = ($3->type == DVAL)?$3->dval:(double)$3->bval;
			$$->dval = a/b;	
			} 
			|
	EXPR AND EXPR  {$$->type = BVAL;
			int a = ($1->type == BVAL)?$1->bval:(($1->dval==0)?0:1);
			int b = ($3->type == BVAL)?$3->bval:(($3->dval==0)?0:1);
			$$->bval = a&b;		
			} 
			|
	EXPR OR EXPR   {$$->type = BVAL;
			int a = ($1->type == BVAL)?$1->bval:(($1->dval==0)?0:1);
			int b = ($3->type == BVAL)?$3->bval:(($3->dval==0)?0:1);
			$$->bval = a|b;		
			} 
			|
	EXPR XOR EXPR  {$$->type = BVAL;
			int a = ($1->type == BVAL)?$1->bval:(($1->dval==0)?0:1);
			int b = ($3->type == BVAL)?$3->bval:(($3->dval==0)?0:1);
			$$->bval = a^b;		
			} 
			|
	NOT EXPR  {$$->type = BVAL;
			int a = ($2->type == BVAL)?$2->bval:(($2->dval==0)?0:1);
			$$->bval = a^1;		
			} 
			|
	NUM {$$->dval = $1->dval; $$->type = DVAL;}
	;


%%

int main(void){
	yyparse();
}
