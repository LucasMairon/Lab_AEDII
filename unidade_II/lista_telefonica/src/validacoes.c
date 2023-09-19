#include<stdio.h>
#include<regex.h>
#include<validacoes.h>

const char NOME_PADRAO[] = "[a-zA-Z]+";
const char TELEFONE_PADRAO[] = "([\(0-9\)]{2})([\s0-9\-]{4,5})([0-9]{4})";
const char EMAIL_PADRAO[] = "([a-z0-9\.\-]{2,})@([a-z 0-9]{2,})(\.[a-z]{2,})(\.[a-z]{2,})?";

int isvalidString(char* string,const char* PADRAO,const int FLAG){
    regex_t regex;
    int valor_regex = regcomp(&regex,PADRAO,FLAG);

    if(valor_regex == 0){
        valor_regex = regexec(&regex,string,0,NULL,FLAG);
        if(valor_regex == 0){
            return 1;
        }else{
            printf("padrao invalido,tente novamente\n");
            return 0;
        }
    }else{
        printf("erro na verificacao,tente novamente\n");
        return 0;
    }
}