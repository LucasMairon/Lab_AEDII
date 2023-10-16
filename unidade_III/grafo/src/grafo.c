#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CHAR 100

#define MAX_TAM_VERTICES 167

struct grafo {
  int vertices;
  int arestas;
  Vertice **g;
};

struct vertice {
  int cep;
  char cityName[MAX_CHAR];
  Aresta *arestas;
};

struct aresta {
  int v;
  Aresta *prox;
};


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


void BuscaCidade(Grafo *gr, char *nome, int id){
  int i = 0, achou = 0;
  if(id == -1 && nome != NULL){
    for (; i < MAX_TAM_VERTICES; i++) {
      if (strcmp(gr->g[i]->cityName, nome) == 0) {
        printf("\nDados da cidade buscada:\n");
        printf("Nome: %s\n", gr->g[i]->cityName);
        printf("CEP: %d\n", gr->g[i]->cep);
        achou++;
      }
    }
  }else if (id >=0 && id < MAX_TAM_VERTICES){
      printf("\nDados da cidade buscada:\n");
      printf("Nome: %s\n", gr->g[id]->cityName);
      printf("CEP: %d\n", gr->g[id]->cep);
      achou++;
  }

  if (achou == 0) {
    printf("\nEssa cidade não existe\n");
  }
}


Vertice *cria_vertice(int cep, char *cidade_nome) {
  Vertice *v = (Vertice *)malloc(sizeof(Vertice));
  strcpy(v->cityName, cidade_nome);
  v->cep = cep;
  v->arestas = NULL;
  return v;
}


Grafo* preencheVertices(Grafo *gr) {
  char linha[MAX_CHAR];
  int CEP, id;
  char nome[MAX_CHAR];
  FILE *cidades = fopen("/workspaces/Lab_AEDII/unidade_III/grafo/data/cidades.txt", "r");
  if (cidades == NULL) {
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }
  while (fgets(linha, MAX_CHAR, cidades) != NULL) {
    sscanf(linha, "%d, %d, %[^\n]", &id, &CEP, nome);
    gr->g[id] = cria_vertice(CEP, nome);
  }
  fclose(cidades);
  return gr;
}


Vertice *cria_aresta(Vertice *lista, int v) {
  if (lista == NULL)
    return NULL;
  Aresta *aresta = (Aresta *)malloc(sizeof(Aresta));
  aresta->v = v;
  aresta->prox = NULL;

  if (lista->arestas == NULL) {
    lista->arestas = aresta;
    return lista;
  }
  aresta->prox = lista->arestas;
  lista->arestas = aresta;
  
  return lista;
}

Grafo *preencher_arestas(Grafo *gr) {
  if (!gr)
    return NULL;
  if (!gr->g)
    return NULL;

  char linha[MAX_CHAR];
  int origem = 0, destino = 0;
  FILE *arestas = fopen("/workspaces/Lab_AEDII/unidade_III/grafo/data/arestas.txt", "r");
  if (arestas == NULL) {
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }
  
  while (fgets(linha, MAX_CHAR, arestas) != NULL) {
    sscanf(linha, "%d %d", &origem, &destino);
     

    if (gr->g[origem] != NULL){
      gr->g[origem] = cria_aresta(gr->g[origem], destino);
      gr->arestas++;
    } else {
      printf("vertice vazio\n");
    }
  }
  fclose(arestas);
  return gr;
}

Grafo *ler_arquivo_arestas_nome(Grafo *gr) {
  if (!gr)
    return NULL;
  if (!gr->g)
    return NULL;

  char linha[MAX_CHAR];
  char vertice_nome[MAX_CHAR];

  int origem = 0, destino = 0;

  FILE *arestas_arquivo = fopen("/workspaces/Lab_AEDII/unidade_III/grafo/data/arestas_nome.txt", "r");
  if (arestas_arquivo == NULL) {
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }

  while (fgets(linha, MAX_CHAR, arestas_arquivo) != NULL) {

    sscanf(linha, " %[^\n]", vertice_nome);

    origem = pegar_vertice(gr, vertice_nome);

    if (origem != -1) {

      while (strcmp(fgets(linha, MAX_CHAR, arestas_arquivo), "\n")) {

        sscanf(linha, " %[^\n]", vertice_nome);
        destino = pegar_vertice(gr, vertice_nome);
        if (destino != -1) {

          gr->g[origem] = cria_aresta(gr->g[origem], destino);
          gr->arestas++;
        } else {
          printf("vertice nao encontrado aresta: %s\n", vertice_nome);
        }
      }
    } else {
      printf("vertice nao encontrado: %s\n", vertice_nome);
      while (strcmp(fgets(linha, MAX_CHAR, arestas_arquivo), "\n")) {
        sscanf(linha, " %[^\n]", vertice_nome);
      }
    }
  }

  printf("%d\n", gr->arestas);

  fclose(arestas_arquivo);
  return gr;
}


int pegar_vertice(Grafo *gr, char *nome) {
  int i = 0;
  for (; i < MAX_TAM_VERTICES; i++) {
    if (!strcmp(gr->g[i]->cityName, nome)) {
      return i;
    }
  }
  return -1;
}


Grafo *iniciar_grafo() {
  Grafo *g = cria_grafo();
  g = preencheVertices(g);
  g = preencher_arestas(g);
  return g;
}


void informacoes_busca(Grafo* gr){
  printf("\nformato:");
  printf("\n[id] - nome\n\n");
  for (int i = 0; i < MAX_TAM_VERTICES; i++){
    printf("[%d] - %s\n", i, gr->g[i]->cityName);
  }
}