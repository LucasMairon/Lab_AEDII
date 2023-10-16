#include <stdio.h>
#include<stdlib.h>
#include"grafo.c"
#include"validacoes.c"
#include<locale.h>

#define MAX_CHAR 100
int menu();
int menu_busca();

int main(){
  system("clear");
  setlocale(LC_ALL, "Portuguese");
  Grafo* g = iniciar_grafo();
  int escolha = 0, opcao_busca = 0, id = 0;
  char* nomeCidade = (char*)malloc(sizeof(char)*MAX_CHAR);
  printf("Descrição sobre o grafo:\n");
  printf("os vertices do grafo representam as cidades do estado Rio Grande do Norte e as arestas representam as cidades vizinhas;\n");
  printf("quantidade de arestas: %d\n",g->arestas);
  printf("quantidade de vertices: %d\n",g->vertices);
  
do{
  escolha = menu();
  switch(escolha){
    case 1:
      printf("\nListar cidades e suas vizinhas:\n");
      ImprimeGrafo(g);
    break;
    case 2:
      printf("\nBuscar cidade:\n");
      opcao_busca = menu_busca();
      if(opcao_busca == 1){
        printf("digite o nome da cidade que deseja buscar(com nomes em maiusculo): ");
        scanf(" %[^\n]",nomeCidade);
        BuscaCidade(g, nomeCidade, -1);
      }else if (opcao_busca == 2){
        printf("digite o id da cidade que deseja buscar(com nomes em maiusculo): ");
        id = capturaNumero();
        BuscaCidade(g, NULL, id);
      }else if (opcao_busca == 3){
        informacoes_busca(g);
      }else{
        printf("opção invalida\n");
      }
      
    break;
    case 3:
      printf("\nSair:\n");
      printf("finalização do programa;\n");
      liberaGrafo(g);
      free(nomeCidade);
    break;
    default:
      printf("\nopção inválida\n");
    break;
  }
}while(escolha != 3);

}

int menu(){
  printf("\n");
  printf("1 - Listar cidades e suas vizinhas\n");
  printf("2 - Buscar cidade\n");
  printf("3 - Sair\n");
  return capturaNumero();
}

int menu_busca(){
  printf("\n");
  printf("1 - Buscar por nome\n");
  printf("2 - Buscar por Id\n");
  printf("3 - informações de busca\n");
  return capturaNumero();
}

