// 4. Um n´umero inteiro ´e considerado um n´umero perfeito se seus fatores, incluindo 1 (mas n˜ao o
// pr´oprio n´umero), somam o n´umero. Por exemplo, 6 ´e um n´umero perfeito porque 6 = 1 + 2 + 3.
// Escreva uma fun¸c˜ao isPerfect que determina se o n´umero do parˆametro ´e um n´umero perfeito. Use
// esta fun¸c˜ao em um programa que determina e imprime todos os n´umeros perfeitos entre 1 e 1000.
// Imprima os fatores de cada n´umero perfeito para confirmar que o n´umero ´e realmente perfeito.

#include<stdio.h>
#include<math.h>

int isPerfect(int n){
    int soma =0, i;
    for(i = 1; i < n; i++)
        if((n % i) == 0)
            soma += i;
    return (soma == n);
}

void imprimePerfeito(int p){
    int i;
    printf("%d é Perfeito!\n",p);
    printf("%d ",1);
    for(i = 2; i < p; i++)
        if((p % i) == 0)
            printf("+ %d ",i);
    printf("= %d\n",p);
}

void Perfeito(int inicio, int fim){
    int i;
    for(i = inicio; i < fim; i++)
        if(isPerfect(i))
            imprimePerfeito(i);
    
}


int main(){
    Perfeito(1, 1000);
}