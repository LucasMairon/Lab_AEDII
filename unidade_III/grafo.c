#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CHAR 100

#define MAX_TAM_VERTICES 167

// struct que representa um grafo, nela temos a variavel que guarda a quantidade
// de vertices, a que guarda a quantidade de arestas e a matriz de adjacencia
struct grafo {
  int vertices;
  int arestas;
  Vertice **g;
};

// struct que representa um vertice, temos a variavel que guarda o id do vertice
// e o ponteiro para o proximo vertice
struct vertice {
  // int vertice; ??????
  int cep;
  char cityName[MAX_CHAR];
  Aresta *arestas;
};

struct aresta {
  int v;
  Aresta *prox;
};

// cria a inicializa o grafo
Grafo *cria_grafo() {
  Grafo *gr = (Grafo *)malloc(sizeof(Grafo));
  gr->g = (Vertice **)malloc(sizeof(Vertice *) * MAX_TAM_VERTICES);
  gr->vertices = MAX_TAM_VERTICES;
  gr->arestas = 0;
  for (int i = 0; i < MAX_TAM_VERTICES; i++) {
    gr->g[i] = NULL;
  }
  return gr;
}


void liberaGrafo(Grafo *gr) {
  if (!gr)
    return;
  int i = 0;
  Aresta *lista_adj = NULL;
  Aresta *liberar = NULL;

  for (i = 0; i < MAX_TAM_VERTICES; i++) {
    lista_adj = gr->g[i]->arestas;
    while (lista_adj != NULL) {
      liberar = lista_adj;
      lista_adj = lista_adj->prox;
      free(liberar);
    }
    free(gr->g[i]);
  }
  free(gr->g);
  free(gr);
}

void imprimeDadosCidade(int i, Grafo* gr) {
  printf("\nDados da cidade:\n");
  printf("Nome da cidade: %s\n", gr->g[i]->cityName);
  printf("CEP: %d\n", gr->g[i]->cep);
  printf("Cidades vizinhas:\n");
  Aresta* aux = gr->g[i]->arestas;

  for (; aux != NULL; aux = aux->prox) {
    printf("%s", gr->g[aux->v]->cityName);
    if(aux->prox != NULL){
      printf(", ");
    }
  }
  printf(";");
}

void ImprimeGrafo(Grafo *gr) {
  if (!gr)
    return;
  int i = 0;
  for (; i < MAX_TAM_VERTICES; i++) {
    printf("\n");
    imprimeDadosCidade(i, gr);
  }
  printf("\n");
}

void BuscaCidade(Grafo *gr, char *nome) {
  int i = 0, achou = 0;
  for (; i < MAX_TAM_VERTICES; i++) {
    if (strcmp(gr->g[i]->cityName, nome) == 0) {
      printf("\nDados da cidade buscada:\n");
      printf("Nome: %s\n", gr->g[i]->cityName);
      printf("CEP: %d\n", gr->g[i]->cep);
      achou++;
    }
  }
  if (achou == 0) {
    printf("\nEssa cidade não existe\n");
  }
}