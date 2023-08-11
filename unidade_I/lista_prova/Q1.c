// 1. Escreva um programa para converter e imprimir os caracteres para os valores ASCII de 0 a 127.
// O programa deve imprimir 10 caracteres por linha.
#include <stdio.h>

int main(){

    int i, j = 0;
    char c;

    for (i = 0; i < 127; i++){
        c = i;
        printf(" %c", c);
        j++;
        if (j == 9){
            printf("\n");
            j = 0;
        }
    }

    return 0;
}