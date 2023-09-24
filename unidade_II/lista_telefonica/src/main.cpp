#include"contato.cpp"
#include"validacoes.cpp"
#include<locale.h>

int menu();

int main(){
    system("clear");
    setlocale(LC_ALL,"Portuguese");

    ListaContatos* hashAgenda[SIZE_HASH_TABLE];
    iniciar_agenda(hashAgenda);
    ler_agenda(hashAgenda);
    ListaContatos* listaDeContatos = NULL;
    int escolha;
    char* nome;
    char* email;
    char* telefone;
    char caminho[MAX_CHAR];
    
    do{
        escolha = menu();

    switch(escolha){
        case 1:
            printf("\nCriar contato:\n");
            printf("digite o nome do contato: ");
            nome = capturaNome();
            printf("digite o email do contato(email@dominio.complemento.complementoopcional): ");
            email = capturaEmail(EMAIL_PADRAO,FLAG);
            printf("digite o telefone do contato(formato:(dd) nnnnn-nnnn): ");
            telefone = capturaTelefone();
            listaDeContatos = criar_contato(nome,email,telefone);
            inserir(hashAgenda,listaDeContatos);
            printf("contato inserido com sucesso");
            
        break;

        case 2:
            printf("\nListar agenda:\n");
            listar_agenda(hashAgenda); 
            break;
        case 3:
            printf("\nExportar contatos:\n");
            printf("digite o caminho para onde deseja exportar seus contatos(use uma pasta que já existe): ");
            scanf(" %[^\n]",caminho);
            exportar(hashAgenda,caminho);
            printf("seus contatos foram exportados para: %s",caminho);

        break;

        case 4:
            printf("\nBuscar contato:\n");
            printf("digite o nome do contato que deseja buscar: ");
            nome = capturaNome();
            listaDeContatos = busca(hashAgenda,nome);
            listar_contato(listaDeContatos);
        break;

        case 5:
            printf("\nRemover contato:\n");
            printf("digite o nome do contato que deseja remover: ");
            nome = capturaNome();
            listaDeContatos = removeContatos(hashAgenda,nome);

            if(listaDeContatos != NULL){
                free(listaDeContatos->info);
                free(listaDeContatos);
                printf("contato removido com sucesso\n");
            }else{
                printf("O contato não está na lista");
            }
        break;

        case 6:
            // printf("digite o nome do contato que deseja editar: ");
            // scanf(" %[^\n]", nome);
            // editar(hashAgenda, nome);
        break;

        case 7:
            printf("\nSair:\n");
            printf("execução finalizada\n");
        break;
        default:
            printf("opção invalida");
        break;
        
    }

    }while(escolha != 7);
    salvar_agenda(hashAgenda);
    liberar_agenda(hashAgenda);
}


int menu(){
    printf("\n");
    printf("1 - Criar contato\n");
    printf("2 - Listar agenda\n");
    printf("3 - Exportar contatos\n");
    printf("4 - Buscar contato\n");
    printf("5 - Remover contato\n");
    printf("6 - Editar contato\n");
    printf("7 - Sair\n");
    
    return capturaNumero();
    
}
