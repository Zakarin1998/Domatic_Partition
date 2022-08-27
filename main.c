#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "ST.h"

enum { f , t };

//DOMATIC CHECK : VERIFICA CHE OGNI SET DELLA PARTIZIONE DI ORDINE k SIA DOMINATING
int checkDomaticPartition(Graph G,int *sol, int k){
	int i,j, *set;
	int count = 0;
	int flag = f;
	set = calloc(G->V,sizeof(int));
	if(set==NULL) exit(-1);
	
	//GENERO IL SET in base al partizionamento
	for(j=0; j<k ; j++){//per ogni set della partizione
	
		//1. GENERO IL VETTORE SET
		for(i=0 ; i<G->V; i++){//scorri vettore partizione sol
			if(sol[i] == j){//trovato elemento appartenente alla partizione
				set[i] = 1;
				count++;
			}
		}
		//2. VERIFICO CHE IL SET SIA DOMINATING
		if(checkDominatingSet(G,set)){//se il set e' dominante
			flag = t;
		}else{//se un set set non e' dominating
			return f;
		}
	}
	free(set);
	return flag;
}

//ALGORITMO ER
int generaPartizioni(Graph G, int n, int m, int pos, int *sol, int k){
    int i;
    
    //CASO TERMINALE
    if(pos >= n){
        if(m == k){
            if(checkDomaticPartition(G, sol, k))//VERIFICO SE LA PARTIZIONE E' DOMATIC
                return 1;
            return 0;
        }
        return 0;
    }
    
    //CORPO RICORSIVO
    for(i=0; i<m; i++){
        sol[pos] = i;
        if(generaPartizioni(G, n, m, pos+1, sol, k))
            return 1;
    }
    sol[pos] = m;
    if(generaPartizioni(G, n, m+1, pos+1, sol, k))
        return 1;
    return 0;
}

//Wrapper : GENERA PARTIZIONE , LA SALVA SU FILE , AGGIORNA IL VALORE MASSIMO DI CARDINALITA'
void generaDomatic(Graph G){
    int *sol,i;
    FILE *fout;
    sol = calloc(G->V,sizeof(int));
    fout = fopen("proposta.txt","w");
    if(fout==NULL) exit(-1);
    for(i = G->V; i<G->V; i--){//ciclo di cardinalita da n a 1
        if(generaPartizioni(G, G->V, 0, 0, sol, i)) {//se la partizione generata e' domatic
            printf("Soluzione valida con %d partizioni:\n",i);
            for (i = 0; i < G->V; i++) {
            	printf("%d ",sol[i]);
            	//salva su file la partizione giusta
            	fprintf(fout,"%d ",sol[i]);
            }
    	}
	}
	fclose(fout);
}

int main(int argc, char **argv){
	//DICHIARAZIONI VARIABILI
	int id;
    FILE *fin, *fout;
    Graph G;
    int *part,i,tmp;
    
    //ACQUISIZIONE GRAFO E SALVATAGGIO IN STRUTTURA DATI
    fin = fopen("g.txt", "r");
    if( fin == NULL) exit(-1);
    G = GRAPHreadFile(fin);
    fclose(fin);
    
    //SI INDIVIDUI LA DOMATIC PARTITION A CARDINALITA' MASSIMA
    generaDomatic(G);
    
    //FINE PROGRAMMA
    GRAPHfree(G);
    
    return 0;
    
}

//si sceglie di non utilizzare questa funzione nel main
int checkPartition(Graph G, FILE *fin){
	int i, *tmp;
	int nPart=0; //numero di partizioni
	int flag = 1;
	tmp = malloc(G->V*sizeof(int)); //vettore di partizione (dinamico)
	part = malloc(G->V * sizeof(int)); //partizione corrente (riallocato ogni volta)int flag = 1;
	//APERTURA FILE proposta.txt
	fin = fopen("partition.txt","r");
	if(fin==NULL) exit(-1);
	//LEGGI FILE
	for(i=0;i<G->V;i++)
		fscanf(fin, "%d ", &tmp[i]);//riempio un vettore partizioni
	//VERIFICA CHE OGNI PARTIZIONE SIA DOMINATING SET
	for(i=0 ; i<G->V ; i++){//scansiona vettore tmp
		if(tmp[i]>nPart)//trovato nuovo massimo
			nPart=tmp[i];//aggiorna numero partizioni
	}
	nPart++;//aumento di 1 : se il valore più alto di tmp[i] e' 2, significa che ci sono 3 partizioni (p0, p1, p2)
	flag = checkDomaticPartition(G,tmp,nPart);
	
	free(tmp);
	return flag;
}