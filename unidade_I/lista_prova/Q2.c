// 2. Defina uma fun¸c˜ao chamada diasDeAula que calcula quantas aulas de laborat´orio temos dado
// como entrada: Dia de hoje(dia,mˆes,ano) e Ultimo dia do Semestre(dia,mˆes,ano). 

#include<stdio.h>

int diasDeAula(int dia, int mes, int ano){
    int ultimoDia = 30, ultimoMes = 10, ultimoAno = 2023; 
    ano *= 365;
    mes *= 30;
    dia += mes + ano;
    ultimoAno *= 365;
    ultimoMes *= 30;
    ultimoDia += ultimoMes + ultimoAno;
    int dias = 2*(ultimoDia - dia)/7;
    return dias;
}


int main(){
    int dia, mes, ano;
    printf("digite o dia:");
    scanf("%d",&dia);
    printf("digite o mes:");
    scanf("%d",&mes);
    printf("digite o ano:");
    scanf("%d",&ano);
    printf("quantos aulas faltam: %d",diasDeAula(dia, mes, ano));

}