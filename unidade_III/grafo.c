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