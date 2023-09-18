#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CHAR 100
#define SIZE 32 

typedef struct listaContatos ListaContatos;
typedef struct contato Contato;
//typedef struct contato *AgendaDeContatos[SIZE];

struct contato{
  char nome[MAX_CHAR];
  char email[MAX_CHAR];
  char telefone[MAX_CHAR]; // 11 digitos
};

struct listaContatos{
  Contato* info;
  ListaContatos* prox;
  ListaContatos* ant;
};


int concatenaa(char* nome){
  int count = 0;
  int soma = nome[count];
  while(nome[count] != 0){
    soma += nome[count];
    count++;
  }
  return soma;
}

typedef unsigned long long int numeroGrande;

int multiplicacao(numeroGrande key){
  key *= key;
  int digits = ceil(log2((numeroGrande)540000 * 540000));
    int signif = ceil(log2(SIZE - 1));
    float remover = digits - signif;
    int digitMask = (int)ceil(remover / 2);
    numeroGrande mask = ((SIZE-1) << digitMask);
    key = key & mask;
    key = (key >> digitMask);
    return key;
}


Contato* Preencher_dados(char* nome, char* email,char* telefone){
  Contato* novo = (Contato*)malloc(sizeof(Contato));
  strcpy(novo->nome,nome);
  strcpy(novo->email,email);
  strcpy(novo->telefone,telefone);
  return novo;
}


ListaContatos* criar_contato(char* nome, char* email,char* telefone){
  ListaContatos* novo = (ListaContatos*)malloc(sizeof(ListaContatos));
  novo->info = Preencher_dados(nome, email,telefone);
  novo->prox = NULL;
  novo->ant = NULL;
  return novo;
}


// void inserir(AgendaDeContatos* hashAgenda, Contato* contato){
void inserir(ListaContatos** hashAgenda, ListaContatos* contato){
  //int key = hash_multt(concatenaa(contato->info->nome));
  int key = multiplicacao(concatenaa(contato->info->nome));
  
  if(hashAgenda[key] == NULL){
    hashAgenda[key] = contato;
  }else{
    ListaContatos* aux = hashAgenda[key];
    printf("fazer a tratativa aqui!!!\n");
    for(; aux->prox != NULL; aux = aux->prox){
      
    }
  aux->prox = contato;
  contato->ant = aux;
  contato->prox = NULL;
  }
}


void listar_agenda(ListaContatos* contato){
  ListaContatos* aux = contato;
  for(; aux != NULL; aux = aux->prox){  
  printf("nome: %s\nemail: %s\ntell: %s\n",aux->info->nome,aux->info->email, aux->info->telefone);
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

  for(i = 0; i<SIZE; i++)
     for(aux = hashAgenda[i]; aux!= NULL; aux = aux->prox)
       fprintf(agenda,"nome: %s\nemail: %s\ntell: %s\n",aux->info->nome,aux->info->email, aux->info->telefone);

  fclose(agenda);
}

void ler_agenda(ListaContatos** hashAgenda){
  char linha[MAX_CHAR], nome[MAX_CHAR], email[MAX_CHAR], telefone[MAX_CHAR];
  //int key; 
  FILE* agenda = fopen("/workspaces/Lab_AEDII/unidade_II/lista_telefonica/date/agenda.txt", "r");
  if(agenda == NULL){
    printf("erro na abertura do arquivo!!\n");
    exit(1);
  }

  while(fgets(linha,MAX_CHAR,agenda) != NULL){
    sscanf(linha,"nome: %[^\n]",nome);
    fgets(linha,MAX_CHAR,agenda);
    sscanf(linha,"email: %[^\n]",email);
    fgets(linha,MAX_CHAR,agenda);
    sscanf(linha,"telefone: %[`\n]", telefone);

    inserir(hashAgenda ,criar_contato(nome, email,telefone));
  }
}

ListaContatos* busca(ListaContatos** agenda, char* nome){
  int key = multiplicacao(concatenaa(nome));

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
    int key = multiplicacao(concatenaa(nome));
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


// void edit(Contato** agenda, char* nome){
//   Contato* contato = removeContato(agenda,nome);
//   int escolha = 0, sair = 0;
 
//   do{

//     // fazer dois menus um para escolha e outro para sair 

//     escolha = getNumero(msg); // ta pra ser feita usando regEx

//   switch (escolha){
//     case 1:
//       contato->info->nome = getNome(msg);// ta pra ser feita com regex
//      break;
//     case 2:
//       contato->info->email = getEmail("email"); // ta pra ser feita Com regex
//      break;
//     case 3:
//       contato->info->tel = getTelefone(msg); //ta pra ser feita com regex;
//      break;
//     case 4:
//     // copiar e colar os de cima 
//     default:
//      break;
//   }
//    sair = getNumero(msg); // ta pra ser feita usando regEx;
    
//   }while(sair != 1);

//   inserir(agenda, contato);
// }



void iniciar_agenda(ListaContatos** agenda){
    for(int i = 0; i<SIZE; i++){
      agenda[i] = NULL;
    }
}


// int main(void) {
//   printf("Hello World\n");

//   ListaContatos* agenda[SIZE];
//   iniciar_agenda(agenda);

//   ler_agenda(agenda);
  
//   inserir(agenda,criar_contato("lidiana","lidi@gmail.com", "84999999999"));
//   inserir(agenda,criar_contato("ana","lidi@gmail.com","84999999999"));
//   inserir(agenda,criar_contato("lidiana costa ","lidi@gmail.com", "84999999999"));

//   inserir(agenda,criar_contato("lidiana","lidi@gmail.com", "84999999999"));

//   inserir(agenda,criar_contato("lucas mairon ","lidi@gmail.com", "84999999999"));

//   inserir(agenda,criar_contato("ana regina","lidi@gmail.com", "84999999999"));


  
//   for(int i = 0; i<SIZE; i++){
//     if(agenda[i] != NULL){
//       printf("\n%d\n",i);
//       listar_agenda(agenda[i]);
//     }
//   }

//   // removeContato(agenda,"lidiana");
//   // removeContato(agenda,"lidiana");
  
//   // printf("\n\n");
//   // listar_agenda(busca(agenda, "lidiana"));
  
//    exportar(agenda);

//   return 0;
// }