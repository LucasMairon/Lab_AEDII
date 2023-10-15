#include <stdio.h>
#include<stdlib.h>
#include "grafo.h"
#include"validacoes.h"
#include<locale.h>

#define MAX_CHAR 100
int menu();

int main(){
  system("clear");
  setlocale(LC_ALL, "Portuguese");
  Grafo* g = iniciar();
  int escolha = 0;
  char* nomeCidade = (char*)malloc(sizeof(char)*MAX_CHAR);
  
do{
  escolha = menu();
  switch(escolha){
    case 1:
      printf("Listar cidades e suas vizinhas:\n");
      // ImprimeGrafo(g);
      //imprime(g);
      
    break;
    case 2:
      printf("Buscar cidade:\n");
      printf("digite o nome da cidade que deseja buscar(com nomes em maiusculo): ");
      scanf(" %[^\n]",nomeCidade);
      //BuscaCidade(g, nomeCidade);
    break;
    case 3:
      printf("Sair:\n");
      printf("finalização do programa\n");
      //liberaGrafo(g);
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


