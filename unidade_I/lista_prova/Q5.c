//5. Defina uma fun¸c˜ao recursiva que, dado os valores inteiros de x1 e x2, determine y = x1x2.

#include<stdio.h>
#include<math.h>

int produtorio(int x1, int x2){
    if(x2 == 0)
        return 0;
    
    if(x2 == 1)
        return x1;
    
    return x1 + produtorio(x1, x2 -1);
    
}

int main(){
    int a = 5 ,b = 2;
    printf("Produto de %d por %d é igual ha %d", a, b, produtorio(a,b));
}