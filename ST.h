#ifndef ST_H_DEFINED
#define ST_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct symboltable *ST;

ST  	STinit(int maxN);
void    STfree(ST st);
int  	STinsert(ST st, char *s);
int     STsearch(ST st, char *s);
int		STcount(ST st);
char    *STsearchByIndex(ST st, int i);

#endif