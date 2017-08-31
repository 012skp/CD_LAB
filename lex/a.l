%{
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

%}

LETTER [A-Za-z_]
DIGIT [0-9]
HEXD [0-9A-Fa-f]
NUMBER (0x{HEXD}+)|(({DIGIT}+)(\.{DIGIT}+)?([\Ee][\+-]?{DIGIT})?)
DELIM [ \t\n]
WS {DELIM}+
LD ({LETTER}{DIGIT})
ID  {LETTER}({LETTER}|{DIGIT})*
PREP (#[^\n]*)
SYM ([;\.,(){}\[\]])
OP (\+|-|\*|\/|\%|\+=|-=|\*=|\/=|\%=|=|==|<|>|<=|>=|\+\+|--|->|&|\||^|~|&=|^=|\|=) 
SLC (\/\/[^\n]*)
MLC (\/\*[^(\*\/)]*\*\/)
STRING (\"([^\"]|(\\\"))*\")

%%
{SLC} {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" => SINGLE LINE COMMENT\n",yytext);}
{MLC} {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" => MULTILINE COMMENT\n",yytext);}
{ID} {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET"  =>  IDENTIFIER\n",yytext);}
{NUMBER} {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" => NUMBER\n",yytext);}
{PREP} {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" => PREPROCESSING TEXT\n",yytext);}
{STRING}  {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" => STRING CONSTANT\n",yytext);}
{OP} {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" => Operator\n",yytext);}
{SYM} {printf(ANSI_COLOR_RED"%s"ANSI_COLOR_RESET" => SYMBOLS\n",yytext);}
{WS} {}
. {printf("%s => not defined yet\n",yytext);}
%%

