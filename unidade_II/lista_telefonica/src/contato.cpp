#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "contato.h"

#define MAX_CHAR 100
#define SIZE_HASH_TABLE 32

struct contato{
  char nome[MAX_CHAR];
  char email[MAX_CHAR];
  char telefone[MAX_CHAR];
};

struct listaContatos{
  Contato* info;
  ListaContatos* prox;
  ListaContatos* ant;
};


int concatena(char* nome){
  int count = 0;
  int soma = nome[count];
  while(nome[count] != 0){
    soma += nome[count];
    count++;
  }
  return soma;
}


int hash_multiplicacao(numeroGrande key){
  key *= key;
  int digits = ceil(log2((numeroGrande)540000 * 540000));
  int signif = ceil(log2(SIZE_HASH_TABLE - 1));
  float remover = digits - signif;
  int digitMask = (int)ceil(remover / 2);
  numeroGrande mask = ((SIZE_HASH_TABLE-1) << digitMask);
  key = key & mask;
  key = (key >> digitMask);
  return key;
}


ListaContatos* criar_contato(char* nome, char* email,char* telefone){
  ListaContatos* listaContatos = (ListaContatos*)malloc(sizeof(ListaContatos));
  Contato* contato = (Contato*)malloc(sizeof(Contato));
  strcpy(contato->nome,nome);
  strcpy(contato->email,email);
  strcpy(contato->telefone,telefone);
  listaContatos->info = contato;
  listaContatos->prox = NULL;
  listaContatos->ant = NULL;
  return listaContatos;
}


void inserir(ListaContatos** hashAgenda, ListaContatos* contato){
  int key = hash_multiplicacao(concatena(contato->info->nome));
  
  if(hashAgenda[key] == NULL){
    hashAgenda[key] = contato;
  }else{
    ListaContatos* aux = hashAgenda[key];
    for(; aux->prox != NULL; aux = aux->prox){
  }

  aux->prox = contato;
  contato->ant = aux;
  contato->prox = NULL;
  }
}


void listar_contato(ListaContatos* contato){
  if (contato != NULL){
   printf("nome: %s\nemail: %s\ntelelefone: %s\n",contato->info->nome,contato->info->email, contato->info->telefone); 
  }
}


void listar_agenda(ListaContatos** agenda){
  ListaContatos* contato; 
  int i =0;
  for(; i<SIZE_HASH_TABLE; i++){
    contato = agenda[i];
    for(; contato != NULL; contato = contato->prox){
      listar_contato(contato);
    }
  }
}


void exportar(ListaContatos** hashAgenda){
  int i;
  ListaContatos* aux;
  FILE* agenda = fopen("/workspaces/Lab_AEDII/unidade_II/lista_telefonica/src/output/agenda.txt", "w");
    if(agenda == NULL){
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }

  for(i = 0; i<SIZE_HASH_TABLE; i++)
     for(aux = hashAgenda[i]; aux!= NULL; aux = aux->prox)
       fprintf(agenda,"nome: %s\nemail: %s\ntelefone: %s\n",aux->info->nome,aux->info->email, aux->info->telefone);

  fclose(agenda);
}


void ler_agenda(ListaContatos** hashAgenda){
  char linha[MAX_CHAR], nome[MAX_CHAR], email[MAX_CHAR], telefone[MAX_CHAR];
  //int key; 
  FILE* agenda = fopen("/workspaces/Lab_AEDII/unidade_II/lista_telefonica/data/agenda.txt", "r");
  if(agenda == NULL){
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }

  while(fgets(linha,MAX_CHAR,agenda) != NULL){
    sscanf(linha,"nome: %[^\n]",nome);
    fgets(linha,MAX_CHAR,agenda);
    sscanf(linha,"email: %[^\n]",email);
    fgets(linha,MAX_CHAR,agenda);
    sscanf(linha,"telefone: %[^\n]", telefone);

    inserir(hashAgenda ,criar_contato(nome, email,telefone));
  }
}


ListaContatos* busca(ListaContatos** agenda, char* nome){
  int key = hash_multiplicacao(concatena(nome));

  if(agenda[key] == NULL){
    printf("O contato não está na agenda\n");
    return NULL;
  }else if(agenda[key]->prox == NULL){
     return agenda[key];
  }else{
    ListaContatos* aux = agenda[key];
    for(; aux !=NULL; aux = aux->prox){
      if(!strcmp(nome, aux->info->nome)){
        return aux;
      }
    }
  }
  return NULL;
}


ListaContatos* removeContatos(ListaContatos** agenda,char* nome){
  ListaContatos* ListaContatos = busca(agenda, nome);
  if(ListaContatos->ant == NULL){  
    int key = hash_multiplicacao(concatena(nome));
    if(ListaContatos->prox == NULL){
      agenda[key] = NULL;
    }else{
    agenda[key] = ListaContatos->prox;
    ListaContatos->prox->ant = NULL;
    return ListaContatos;
    }
  }else if(ListaContatos->prox == NULL){
    ListaContatos->ant->prox = NULL;
    return ListaContatos;
  }else{
    ListaContatos->ant->prox = ListaContatos->prox;
    ListaContatos->prox->ant = ListaContatos->ant;
    return ListaContatos;
  }
  return NULL;
}


void iniciar_agenda(ListaContatos** agenda){
  for(int i = 0; i<SIZE_HASH_TABLE; i++){
    agenda[i] = NULL;
  }
}


void liberar_agenda(ListaContatos**agenda){
  ListaContatos* aux;
  int i = 0;

  for(; i<SIZE_HASH_TABLE; i++){
    if(agenda[i] != NULL){
     aux = agenda[i];
     while(aux->prox != NULL){
      aux = aux->prox;
      free(aux->ant);
     }
     free(aux);
    }
  }
}