typedef struct contato Contato;
typedef struct listaContatos ListaContatos;
typedef unsigned long long int numeroGrande;

int hash_multiplicacao(numeroGrande key);

int concatenaa(char* nome);

Contato* Preencher_dados(char* nome, char* email,char* telefone);

ListaContatos* criar_contato(char* nome, char* email,char* telefone);

void inserir(ListaContatos** hashAgenda, ListaContatos* contato);

void listar_agenda(ListaContatos* contato);

void exportar(ListaContatos** hashAgenda);

void ler_agenda(ListaContatos** hashAgenda);

ListaContatos* busca(ListaContatos** agenda, char* nome);

ListaContatos* removeContatos(ListaContatos** agenda,char* nome);

void iniciar_agenda(ListaContatos** agenda);
