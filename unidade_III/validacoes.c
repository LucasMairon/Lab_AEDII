#include<stdio.h>
#include<ctype.h>
#include"validacoes.h"
#define MAX_CHAR 100

int capturaNumero(){
    char numero[MAX_CHAR];
    int i = 0;
    printf("digite uma opcao: ");
    scanf(" %[^\n]",numero);
    while(numero[i] != '\0'){
        if (!isdigit(numero[i])){
            return 0;
        }
        i++;
    }
    return(atoi(numero)); 
}
