#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

struct symboltable {
	char **a;
	int n, maxN;
	};


ST STinit(int maxN) {
  int i;
  ST st;
  st = malloc(sizeof(*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  st->maxN = maxN;
  st->n = 0;
  st->a = calloc(maxN,sizeof(char *));
  if (st->a == NULL) {
    printf("Memory allocation error\n");
    free(st);
    return NULL;
  }
  for (i=0; i<maxN; i++)
    st->a[i] = NULL;
  return st;
}

int STcount(ST st){
	return st->n;
}

void STfree(ST st) {
  int i;
  for (i = 0; i  < st->maxN; i++)
    if (st->a[i]!=NULL)
      free(st->a[i]);
  free(st->a);
  free(st);
}

int STinsert(ST st, char *s) {
  if(st->n == st->maxN){
  	st->maxN = 2*st->maxN;
  	st->a = realloc(st->a,st->maxN * sizeof(char*));
  }
  st->a[st->n++] = strdup(s);
  return 1;
}

int STsearch(ST st, char *s) {
	int i;
	for (i = 0; i<st->n; i++){
  		if (st->a[i]!=NULL && strcmp(s, st->a[i])==0)
			return i;
	}
	return -1;
}

char *STsearchByIndex(ST st, int i){
	return st->a[i];
}