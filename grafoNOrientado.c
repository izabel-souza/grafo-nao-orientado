#include "grafo.h"

void imprime(TGrafo *g) {

    while(g != NULL) {
        printf("Vertice: %d\n", g->id_vertice);

        TVizinho *v = g->primeiro_vizinho;
        printf("Vizinhos: ");
        while(v != NULL) {
            printf("%d ", v->id_vizinho);
            v = v->prox;
        }
        printf("\n\n");

        g = g->proximo;
    }
}

void libera_vizinhos(TVizinho *v) {
    while(v != NULL) {
        libera_vizinhos(v->prox);
        free(v);
    }
}

void libera_vertices(TGrafo *g) {
    while(g != NULL) {
        libera_vizinhos(g->primeiro_vizinho);
        libera_vertices(g->proximo);
        free(g);
    }
}

TGrafo *busca_vertice(TGrafo *g, int x) {
    while((g != NULL) && (g->id_vertice != x)) {
        g = g->proximo;
    }
    return g;
}

TVizinho *busca_aresta(TGrafo *g, int v1, int v2) {

    TGrafo *pv1 = busca_vertice(g, v1);
    TGrafo *pv2 = busca_vertice(g, v2);
    TVizinho *resp = NULL;

    if((pv1 != NULL) && (pv2 != NULL)) {
        resp = pv1->primeiro_vizinho;
        while((resp != NULL) && (resp->id_vizinho != v2)) {
            resp = resp->prox;
        }
    }
    return resp;
}

TGrafo *insercao_vertices(TGrafo *g, int x) {

    TGrafo *novo = busca_vertice(g, x); //verifica se vertice ja existe, apenas se nao existir, cria um novo
    if(novo == NULL) {
        novo = malloc(sizeof(TGrafo));
        novo->id_vertice = x;
        novo->primeiro_vizinho = NULL;
        novo->proximo = g;
        g = novo;
    }
    return g;
}

void insercao_um_sentido(TGrafo *g, int vertice1, int vertice2) {
    TGrafo *p = busca_vertice(g, vertice1); //procura o vertice que sera ligado ao outro vertice pela aresta
    TVizinho *novo = malloc(sizeof(TVizinho)); //cria um novo vizinho para o vertice encontrado
    novo->id_vizinho = vertice2; //liga o novo vertice ao vertice encontrado no grafo
    novo->prox = p->primeiro_vizinho; //insere o novo vertice no inicio da lista de vizinhos do vertice encontrado
    p->primeiro_vizinho = novo; //atualiza o novo como primeiro vizinho 
}

void insercao_aresta(TGrafo *g, int vertice1, int vertice2) {
    TVizinho *v = busca_aresta(g, vertice1, vertice2);
    if(v == NULL) {
        insercao_um_sentido(g, vertice1, vertice2);
        insercao_um_sentido(g, vertice2, vertice1);
    }
}

void retira_um_sentido(TGrafo *g, int vertice1, int vertice2) {

    TGrafo *p = busca_vertice(g, vertice1);

    if(p != NULL) {
        TVizinho *anterior = NULL;
        TVizinho *atual = p->primeiro_vizinho;

        while((atual) && (atual->id_vizinho != vertice2)) {
            anterior = atual;
            atual = atual->prox;
        }

        if(anterior == NULL) {
            p->primeiro_vizinho = atual->prox;
        }
        else {
            anterior->prox = atual->prox;
        }
        free(atual);
    }
}

void retira_aresta(TGrafo *g, int v1, int v2) {
    TVizinho *v = busca_aresta(g, v1, v2);
    if(v != NULL) {
        retira_um_sentido(g, v1, v2);
        retira_um_sentido(g, v2, v1);
    }
}

TGrafo *retira_vertice(TGrafo *g, int x) {

    TGrafo *p = g;
    TGrafo *ant = NULL;

    /*Procura o vertice a ser removido*/
    while((p != NULL) && (p->id_vertice != x)){
        ant = p;
        p = p->proximo;
    }

    /*Se achou*/
    if(p != NULL) {
	/*Remover as arestas do vértice*/
        while (p->primeiro_vizinho != NULL)
            retira_aresta(g, x, p->primeiro_vizinho->id_vizinho);

	/*Arrumar o encadeamento da lista*/
	/*Lembrar do caso de ser o primeiro elemento*/
        if(ant == NULL) {
            g = p->proximo;
        }

        else {
            ant->proximo = p->proximo;
        }

	/*remover o vértice*/
        free(p);
    }
    return g;
}

int main (void) {

    TGrafo *g = NULL;

    g = insercao_vertices(g, 1);
    g = insercao_vertices(g, 2);
    g = insercao_vertices(g, 3);
    g = insercao_vertices(g, 4);

    insercao_aresta(g, 1, 2);
    insercao_aresta(g, 1, 3);
    insercao_aresta(g, 2, 3);

    imprime(g);

    retira_aresta(g, 3, 2);
    printf("Grafo após exclusão da aresta (3,2): \n\n");
    imprime(g);
    
    g = retira_vertice(g,2);
    printf("Grafo após exclusão do vértice 2: \n\n");
    imprime(g);

    g = retira_vertice(g,4);
    printf("Grafo após exclusão do vértice 4: \n\n");
    imprime(g);

    libera_vertices(g);
    return 0;
}