// 3. Um triˆangulo retˆangulo pode ter lados inteiros. O conjunto do comprimento de trˆes valores
// inteiros para os lados de um triˆangulo retˆangulo ´e chamado de triplo pitag´orico. Esses trˆes lados
// devem satisfazer a rela¸c˜ao de que a soma dos quadrados de dois dos lados ´e igual ao quadrado da
// hipotenusa. Encontre todos os triplos pitag´oricos para cateto1, cateto2 e a hipotenusa, todos com
// at´e o valor de, indicado como parˆametro.


#include<stdio.h>
#include<math.h>

int isPitagorico(int limite){
    int a, b, i, j, c;
    for(i = 1; i <= limite; i++){
        for(j = 1; j <= limite; j++){
            
            a = pow(i,2);
            b = pow(j,2);
            c = sqrt(a+b);
            if((a+b) == (pow(c,2)))
                printf("%d^2 + %d^2 = %d^2\n", i, j, c);
        }
    }
    
}


int main(){
    isPitagorico(10);
}