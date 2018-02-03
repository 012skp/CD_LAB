#include "ch3hdr.h"

struct symtab *symlook(char *s)
{
	char *p;
	struct symtab *sp;
	for(sp = symtab; sp< symtab+NSYMS; sp++)
	{
		if(sp->name && !strcmp(sp->name, s))
			return sp;
		
		if(!sp->name)
		{
			sp->name = strdup(s);
			return sp;
		}
	}
	yyerror("too many symbols");
	exit(1);
}

