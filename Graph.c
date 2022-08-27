#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "ST.h"

#define MAXC 3

static int **MATRIXint(int r, int c, int val);
static Edge EDGEcreate(int v, int w);
static void insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w) {
	Edge e;
  	e.v = v;
	e.w = w;
	return e;
}

static int **MATRIXint(int r, int c, int val){
	int i,j;
	int **t = malloc(r * sizeof(int *));
	for(i=0;i<r;i++) t[i] = malloc(c * sizeof(int));
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			t[i][j] = val;
	return t;
}

Graph GRAPHinit(int V) {
	int v;
	Graph G = malloc(sizeof *G);
	if (G == NULL) return NULL;

	G->V = V;
	G->E = 0;
	G->madj = MATRIXint(V,V,0);
	G->tab = STinit(V);
	if (G->tab == NULL) return NULL;
  	
	return G;
}

void GRAPHfree(Graph G) {
	int v;
	for (v=0; v < G->V; v++)
    	free(G->madj[v]);
    free(G->madj);
	STfree(G->tab);
	free(G);
}

Graph GRAPHreadFile(FILE *fin){
	//DICHIARAZIONI VARIABILI
	int i;
	int nv;
	Graph G;
	int v, w;
	char label[MAXC], v1[MAXC], v2[MAXC];
	int id1, id2;
	//INIZIALIZZA GRAFO di nv VERTICI
	fscanf(fin, "%d", &nv);
	G = GRAPHinit(nv);
	if( G == NULL) return NULL;
	//NOMI DEI NODI
	for(i=0;i<G->V;i++){
		label[0] = 'v';//reset label
		label[1] = i;//aggiungo il numero del vertice
		STinsert(G->tab,label);
	}
	
	//RIEMPI LA STRUTTURA DEL GRAFO, Versione 2
	while(fscanf(fin,"%s %s", v1, v2) == 2){
		id1 = STsearch(G->tab,v1);
		id2 = STsearch(G->tab,v2);
		if(id1>=0 && id2>=0)
			insertE(G,EDGEcreate(id1,id2));
	}
	
	return G;
}

int GRAPHgetIndex(Graph G, char *label) {
	int id;
	id = STsearch(G->tab, label);
	if(id==-1){
		id = STcount(G->tab);
		STinsert(G->tab,label);
	}
	return id;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
	insertE(G, EDGEcreate(id1, id2));
}

static void  insertE(Graph G, Edge e) {
	int v = e.v, w = e.w;
	if(G->madj[v][w]==0)
		G->E++;
	G->madj[v][w] = 1;
	G->madj[w][v] = 1;
}

char *GRAPHVertexname(Graph G, int i){
    return STsearchByIndex(G->tab, i);
}

int checkDominatingSet(Graph G, int *set){
    int i,j, count = 0,flag = 1;
    
    for(i=0; i<G->V; i++){//ciclo sui nodi
    	//controllo se il vertice è in D
    	if(set[i]==1){//nel vettore partition = 1 allora appartiene alla partizione, salto controllo
    		break;
		}else{//vertice non in D (non appartiene alla partizione)
			
			for(j=0; j<G->V; j++){//ciclo sui nodi
            	
				if(set[j]==1){//controllo se il vertice j è  in D, nel caso controllo...
                	if(G->madj[i][j] == 1)//...se vertice i è collegato al vertice j ?
                    	count++;
            	}
            	
        	}
        	//...e' finito il conteggio sui vertici possibilmente adiacenti al vertice i
        	if(count==0){//se count e' ancora 0, non e' connesso a nessun vertice in D
        		return 0;
			}
		}
        
    }
    return flag;
}