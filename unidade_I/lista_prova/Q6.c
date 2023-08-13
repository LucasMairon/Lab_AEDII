// 6. Defina uma fun¸c˜ao para inverter um n´umero. Exemplo:
// f(1234) = 4321
// (a) No formato n˜ao recursivo;
// (b) No formato recursivo.

#include <stdio.h>

int inverterNumerosRecursivo(int inverter, int invertido){
    if ((inverter % 10) == 0)
        return invertido;
    return  inverterNumerosRecursivo(inverter/10,invertido * 10 + (inverter % 10) );
}

int inverterNumeros(int inverter){
    int invertido = 0;
    while (inverter != 0){
        invertido = invertido * 10 + (inverter % 10); 
        inverter = inverter / 10;
    }
    return invertido;
}

int main(){
    int inverter = 987654321, invertido = 0;
    printf("numero a inverter: %d\n", inverter);
    printf("numero invertido: %d\n", inverterNumeros(inverter));
    printf("numero invertido de forma Recursiva: %d\n", inverterNumerosRecursivo(inverter, invertido));
}