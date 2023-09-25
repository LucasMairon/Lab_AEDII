#include<regex.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include"validacoes.h"

#define MAX_CHAR 100

const short int FLAG = REG_EXTENDED;
const char EMAIL_PADRAO[] = "([a-z0-9\.\-]{2,})@([a-z 0-9]{2,})(\.com)(\.[a-z]{2,})?";

int isvalidEmail(char* string,const char* PADRAO,const int FLAG){
    regex_t regex;
    int valor_regex = regcomp(&regex,PADRAO,FLAG);
    if(valor_regex == 0){
        valor_regex = regexec(&regex,string,0,NULL,FLAG);
        regfree(&regex);
        if(valor_regex == 0){
            return 1;
        }else{
            return 0;
        }
    }else{
        printf("erro na verificação,tente novamente\n");
        return 0;
    }
    
}

void capturaEmail(const char* PADRAO,const int FLAG,char* email){
    
    scanf(" %[^\n]",email);
    int cont = 0;
    int valor = isvalidEmail(email,PADRAO,FLAG);
    while(valor != 1){
      printf("padrao inválido, tente novamente: ");
      scanf(" %[^\n]",email);
      valor = isvalidEmail(email,PADRAO,FLAG);
      cont++;
    }
    if(cont > 1){
        printf("validação aceita\n");
    }
   
}


int capturaNumero(){
    char numero[MAX_CHAR];
    int i = 0;
    printf("digite uma opcao: ");
    scanf(" %[^\n]",numero);
    while (numero[i] != '\0'){
        if (!isdigit(numero[i])){
            return 0;
        }
        i++;
    }
    return(atoi(numero)); 
}


int isvalidName(char *string){
  int i = 0;

  while (string[i] != '\0') {
    if (!isalpha(string[i]) && !isspace(string[i])) {
      return 0;
    }
    i++;
  }
  return 1;
}

void capturaNome(char* string){
    
    scanf(" %[^\n]",string);
    int cont = 0;
    int valor = isvalidName(string);
    while(valor != 1){
            
      printf("padrao inválido, tente novamente: ");
      scanf(" %[^\n]",string);
      valor = isvalidName(string);
      cont++;
    
    }
    if(cont > 1){
        printf("validação aceita\n");
    }
}

int isvalidNumber(char *numero){
  int i = 0;

  while (numero[i] != '\0') {
    if (!isdigit(numero[i])) {
      return 0;
    }
    i++;
  }
  return 1;
}

void capturaTelefone(char* telefone){

  int cont = 1;

  scanf(" %[^\n]", telefone);

  int valor = isvalidNumber(telefone);
  int tam = strlen(telefone);

  while (valor != 1 || tam != 11) {
    printf("padrao inválido, tente novamente: ");
    scanf(" %[^\n]", telefone);
    valor = isvalidNumber(telefone);
    tam = strlen(telefone);
    cont++;
  }
  if(cont > 1){
        printf("validação aceita\n");
  }

}
