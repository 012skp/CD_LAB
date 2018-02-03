#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define NSYMS 20

struct symtab{
	char *name;
	double value;
} symtab[NSYMS];

struct symtab *symlook();
	
