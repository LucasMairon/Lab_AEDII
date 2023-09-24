typedef struct contato Contato;
typedef struct listacontatos ListaContatos;
typedef unsigned long long int numeroGrande;

int hash_multiplicacao(numeroGrande key);

int concatena(char* nome);

ListaContatos* criar_contato(char* nome, char* email,int telefone);

void inserir(ListaContatos** hashAgenda, ListaContatos* contato);

void listar_agenda(ListaContatos** agenda);

void exportar(ListaContatos** hashAgenda, char* caminho);

void ler_agenda(ListaContatos** hashAgenda);

ListaContatos* busca(ListaContatos** agenda, char* nome);

ListaContatos* removeContatos(ListaContatos** agenda,char* nome);

void iniciar_agenda(ListaContatos** agenda);

void listar_contato(ListaContatos* contato);

void salvar_agenda(ListaContatos** hashAgenda);