#include <stdio.h>
#include <stdlib.h>

typedef struct vizinho {
    int id_vizinho;
    struct vizinho *prox;
} TVizinho;

typedef struct grafo {
    int id_vertice;
    TVizinho *primeiro_vizinho;
    struct grafo *proximo;
} TGrafo;

void imprime(TGrafo *g);
void libera_vizinhos(TVizinho *v);
void libera_vertices(TGrafo *g);
TGrafo *busca_vertice(TGrafo *g, int x);
TVizinho *busca_aresta(TGrafo *g, int v1, int v2);
TGrafo *insercao_vertices(TGrafo *g, int x);
void insercao_um_sentido(TGrafo *g, int v1, int v2);
void insercao_aresta(TGrafo *g, int v1, int v2);
void retira_um_sentido(TGrafo *g, int v1, int v2);
void retira_aresta(TGrafo *g, int v1, int v2);
TGrafo *retira_vertice(TGrafo *g, int x);