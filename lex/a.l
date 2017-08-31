%{
	// All declarations here.

%}

LETTER [A-Za-z_]
DIGIT [0-9]
NUMBER (({DIGIT}+)(\.{DIGIT}+)?([\Ee][+-]?{DIGIT})?)
DELIM [ \t\n]
WS {DELIM}+
LD ({LETTER}{DIGIT})
ID  {LETTER}({LETTER}|{DIGIT})*{WS}
OP ("+" | "-" | "*" | "/" | "+=" | "-=" | "*=" | "/=" | "<" | ">" | "<=" | ">=" | "=" | "==" | "++" | "--" | "->")
SLE (\/\/) 
SLC {SLE}[^\n]*
MLC ("/*"[^"*/"]*)

%%

{ID} {printf("%s  =>  Identifier\n",yytext);}
. {}
%%

