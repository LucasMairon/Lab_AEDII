#include"contato.cpp"
#include"validacoes.c"
#include<stdio.h>

#define MAX_CHAR 100

int menu();

int main(){
    ListaContatos* hashAgenda[SIZE_HASH_TABLE];
    iniciar_agenda(hashAgenda);
    ler_agenda(hashAgenda);
    ListaContatos* listaDeContatos = NULL;
    int escolha, i =0;
    char nome[MAX_CHAR],email[MAX_CHAR],telefone[MAX_CHAR];
    do{
    escolha = menu();
    
    switch(escolha){
        case 1:
            printf("Criar contato:\n");
            printf("digite o nome do contato: ");
            scanf(" %[^\n]",nome);
            printf("digite o email do contato(email@dominio.complemento.complementoopcional): ");
            scanf(" %[^\n]",email);
            printf("digite o telefone do contato(formato:(dd) nnnnn-nnnn): ");
            scanf(" %[^\n]",telefone);
            listaDeContatos = criar_contato(nome,email,telefone);
            inserir(hashAgenda,listaDeContatos);
            printf("contato inserido com sucesso");
            
        break;

        case 2:
            printf("Listar agenda:\n");
            for ( i = 0; i < SIZE_HASH_TABLE; i++){
                listar_agenda(hashAgenda[i]); 
            }
            break;

        case 3:
            printf("Exportar contatos:\n");
            exportar(hashAgenda);
            printf("seus contatos foram exportados para: ");

        break;

        case 4:
            printf("Buscar contato:\n");
            printf("digite o nome do contato que deseja buscar: ");
            scanf(" %[^\n]",nome);
            listaDeContatos = busca(hashAgenda,nome);
            //printf("nome do contato: %s\ntelefone do contato: %s\nemail do contato: %s\n",listaDeContatos->info->nome,listaDeContatos->info->email,listaDeContatos->info->telefone);
            listar_agenda(listaDeContatos);
        break;

        case 5:
            printf("Remover contato:\n");
            printf("digite o nome do contato que deseja remover: ");
            scanf(" %[^\n]",nome);
            listaDeContatos = removeContatos(hashAgenda,nome);
            free(listaDeContatos->info);
            free(listaDeContatos);
            printf("contato removido com sucesso");
        break;

        case 6:
            //em producao
        break;

        case 7:
            printf("Sair:\n");
            printf("execução finalizada\n");
        break;
        
    }
    }while(escolha != 7);
    
    liberar_agenda(hashAgenda);
}


int menu(){
    int escolha;
    printf("\n");
    printf("1 - Criar contato\n");
    printf("2 - Listar agenda\n");
    printf("3 - Exportar contatos\n");
    printf("4 - Buscar contato\n");
    printf("5 - Remover contato\n");
    printf("6 - Editar contato\n");
    printf("7 - Sair\n");
    printf("digite uma opcao:\n");
    scanf("%d",&escolha);
    return escolha;
}
