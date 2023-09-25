#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "contato.h"
#include"validacoes.cpp"

#define MAX_CHAR 100
#define SIZE_HASH_TABLE 32

struct contato{
  char nome[MAX_CHAR];
  char email[MAX_CHAR];
  char telefone[MAX_CHAR];
};

struct listacontatos{
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
    printf("\n");
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


void exportar(ListaContatos** hashAgenda, char* caminho){
  int i;
  ListaContatos* aux;
  FILE* arquivoAgenda = fopen(caminho, "w");
    if(arquivoAgenda == NULL){
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }
  fprintf(arquivoAgenda,"Contatos:\n");
  for(i = 0; i<SIZE_HASH_TABLE; i++)
     for(aux = hashAgenda[i]; aux!= NULL; aux = aux->prox)
       fprintf(arquivoAgenda,"nome: %s\nemail: %s\ntelefone: %s\n",aux->info->nome,aux->info->email, aux->info->telefone);

  fclose(arquivoAgenda);
}


void ler_agenda(ListaContatos** hashAgenda){
  char linha[MAX_CHAR], nome[MAX_CHAR], email[MAX_CHAR], telefone[MAX_CHAR];
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
  fclose(agenda);
}


void salvar_agenda(ListaContatos** hashAgenda){
  int i;
  ListaContatos* aux;
  FILE* agenda = fopen("/workspaces/Lab_AEDII/unidade_II/lista_telefonica/data/agenda.txt", "w");
    if(agenda == NULL){
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }

  for(i = 0; i<SIZE_HASH_TABLE; i++)
     for(aux = hashAgenda[i]; aux!= NULL; aux = aux->prox)
       fprintf(agenda,"nome: %s\nemail: %s\ntelefone: %s\n",aux->info->nome,aux->info->email, aux->info->telefone);

  fclose(agenda);
}


ListaContatos* busca(ListaContatos** agenda, char* nome){
  int key = hash_multiplicacao(concatena(nome));

  if(agenda[key] == NULL){
    printf("O contato não está na agenda\n");
    return NULL;
  }else if(agenda[key]->ant == NULL && agenda[key]->prox == NULL){
     return agenda[key];
  }else{
    ListaContatos* aux = agenda[key];
    for(; aux != NULL; aux = aux->prox){
      if(!strcmp(nome, aux->info->nome)){
        return aux;
      }
    }
  }
  return NULL;
}


ListaContatos* removeContatos(ListaContatos** agenda,char* nome){
  ListaContatos* aux;
  ListaContatos* listaDeContatos = busca(agenda, nome);
  
  if(listaDeContatos == NULL){
    return NULL;
  }

  if(listaDeContatos->ant == NULL){  
    int key = hash_multiplicacao(concatena(nome));
    if(listaDeContatos->prox == NULL){
      aux = agenda[key];
      agenda[key] = NULL;
      return aux;
    }else{
      agenda[key] = listaDeContatos->prox;
      listaDeContatos->prox->ant = NULL;
      return listaDeContatos;
    }
  }else if(listaDeContatos->prox == NULL){
    listaDeContatos->ant->prox = NULL;
    listaDeContatos->ant = NULL;
    return listaDeContatos;
  }else{
    listaDeContatos->ant->prox = listaDeContatos->prox;
    listaDeContatos->prox->ant = listaDeContatos->ant;
    listaDeContatos->ant = NULL;
    listaDeContatos->prox = NULL;
    return listaDeContatos;
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



void menu_editar(){
  printf("\n");
  printf("Menu de edição de contato:\n");
  printf("1 - editar o nome\n");
  printf("2 - editar o email\n");
  printf("3 - editar o telefone\n");
  printf("4 - editar todas as informações do contato\n");
  printf("5 - cancelar a ediçao\n");
  printf("6 - sair!\n");
}


void editar(ListaContatos** agenda, char* nome){
  ListaContatos* contato = busca(agenda, nome);
  ListaContatos* remover = NULL;

  if(contato == NULL){
    return;
  }

  int sair = 0, opcao = 0, r = 0;
  char* novoNome = (char*)malloc(sizeof(char)*MAX_CHAR);
  char* novoEmail = (char*)malloc(sizeof(char)*MAX_CHAR);
  char* novoTelefone = (char*)malloc(sizeof(char)*MAX_CHAR);

  strcpy(novoNome, contato->info->nome);
  strcpy(novoEmail,contato->info->email);
  strcpy(novoTelefone, contato->info->telefone);

  do{
      menu_editar();
      opcao = capturaNumero();
    
    switch (opcao){
    case 1:
      printf("digite o novo nome do contato: ");
      capturaNome(novoNome);
      r++;
      break;
    case 2:
      printf("digite o novo email do contato(email@dominio.complemento.complementoopcional): ");
      capturaEmail(EMAIL_PADRAO, FLAG, novoEmail);
      strcpy(contato->info->email, novoEmail);
      break;
    case 3:
      printf("digite o telefone do contato(formato:ddnnnnnnnnn): ");
      capturaTelefone(novoTelefone);
      strcpy(contato->info->telefone, novoTelefone);
      break;
    case 4:
      printf("digite o novo nome do contato: ");
      capturaNome(novoNome);
      printf("digite o novo email do contato(email@dominio.complemento.complementoopcional): ");
      capturaEmail(EMAIL_PADRAO, FLAG, novoEmail);
      printf("digite o telefone do contato(formato:ddnnnnnnnnn): ");
      capturaTelefone(novoTelefone);
      r++;
      break;
    case 5:
      return;
      break;
    case 6:
      sair = 0;
      break;
    default:
      sair = 1;
      break;
    }

    if(sair != 1){
      printf("\n");
      printf("Dados:\n");
      printf("nome: %s\nemail: %s\ntelefone: %s\n", novoNome, novoEmail, novoTelefone);
      printf("\n");
      printf("deseja fazer mais alguma alteração ?\n1 - sim\n2 - não\n");
      opcao = capturaNumero();
      while(opcao != 1 && opcao != 2){
        printf("deseja fazer mais alguma alteração ?\n1 - sim\n2 - não\n");
        opcao = capturaNumero();
      }

      if(opcao == 1){
        sair = 2;
      }else{
        sair = 0;
      }
    }
  }while(sair != 0);

  if(r != 0){
    inserir(agenda, criar_contato(novoNome, novoEmail, novoTelefone));
    printf("contato atualizado:\n");
    remover = removeContatos(agenda, nome);
    free(remover->info);
    free(remover);
  }

  free(novoNome);
  free(novoEmail);
  free(novoTelefone);
}
