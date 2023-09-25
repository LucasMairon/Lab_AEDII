#include "contato.cpp"
#include <locale.h>

int menu();

int main()
{
  system("clear");
  setlocale(LC_ALL, "Portuguese");

  ListaContatos *hashAgenda[SIZE_HASH_TABLE];
  iniciar_agenda(hashAgenda);
  ler_agenda(hashAgenda);
  ListaContatos *listaDeContatos = NULL;
  int escolha = 0;
  char *nome;
  nome = (char *)malloc(sizeof(char) * MAX_CHAR);
  char *email;
  email = (char *)malloc(sizeof(char) * MAX_CHAR);
  char *telefone;
  telefone = (char *)malloc(sizeof(char) * MAX_CHAR);
  char *caminho;
  caminho = (char*)malloc(sizeof(char)*MAX_CHAR);
  do
  {
    escolha = menu();

    switch (escolha)
    {
    case 1:

      printf("\nCriar contato:\n");
      printf("digite o nome do contato: ");
      capturaNome(nome);
      printf("digite o email do contato(email@dominio.com.complementoopcional): ");
      capturaEmail(EMAIL_PADRAO, FLAG, email);
      printf("digite o telefone do contato(formato:ddnnnnnnnnn): ");
      capturaTelefone(telefone);
      listaDeContatos = criar_contato(nome, email, telefone);
      inserir(hashAgenda, listaDeContatos);
      printf("contato inserido com sucesso");

    break;
    case 2:

      printf("\nListar agenda:\n");
      listar_agenda(hashAgenda);
    break;
    case 3:

      printf("\nExportar contatos:\n");
      printf("digite o caminho para onde deseja exportar seus contatos(use uma pasta que já existe): ");
      scanf(" %[^\n]", caminho);
      exportar(hashAgenda, caminho);
      printf("seus contatos foram exportados para: %s", caminho);

    break;
    case 4:

      printf("\nBuscar contato:\n");
      printf("digite o nome do contato que deseja buscar: ");
      capturaNome(nome);
      listaDeContatos = busca(hashAgenda, nome);
      listar_contato(listaDeContatos);
    break;
    case 5:

      printf("\nRemover contato:\n");
      printf("digite o nome do contato que deseja remover: ");
      capturaNome(nome);
      listaDeContatos = removeContatos(hashAgenda, nome);

      if (listaDeContatos != NULL){
        free(listaDeContatos->info);
        free(listaDeContatos);
        printf("\ncontato removido com sucesso\n");
      }
      else{
        printf("\nO contato não está na lista\n");
      }

    break;
    case 6:

      printf("digite o nome do contato que deseja editar: ");
      capturaNome(nome);
      editar(hashAgenda, nome);
    break;
    case 7:

      printf("Sair:\n");
      salvar_agenda(hashAgenda);
      liberar_agenda(hashAgenda);
      free(nome);
      free(email);
      free(telefone);
      free(caminho);
      printf("execução finalizada\n");
    break;
    default:
      printf("opção invalida\n");
    break;
    }
  } while (escolha != 7);
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
