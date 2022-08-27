#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ST.h"

typedef struct edge { int v; int w;} Edge;

typedef struct graph *Graph;
struct graph { int V; int E; int **madj; ST tab; };

Graph	GRAPHinit(int V);
void	GRAPHfree(Graph G);
Graph	GRAPHreadFile(FILE *fin);
int		GRAPHgetIndex(Graph G, char *label);
void	GRAPHinsertE(Graph G, int id1, int id2);
char*	GRAPHVertexname(Graph G,int i);
int 	checkDominatingSet(Graph G, int *set);

#endif