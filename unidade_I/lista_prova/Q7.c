// 7. Implemente a seguinte fun¸c˜ao matem´atica f(m, n) definida por partes:
// (a) f(m, n) = m + 1, se n = 1.
// (b) f(m, n) = n + 1, se m = 1.
// (c) f(m, n) = f(m, n − 1) + f(m − 1, n), se m > 1, n > 1.[]

#include <stdio.h>

int f(int m, int n){
    if(n == 1)
        return m + 1;
    if(m == 1)
        return n + 1;
    return  f(m, n - 1) + f(m - 1, n);
}


int main(){
    printf("valor = %d\n", f(2,3));
}