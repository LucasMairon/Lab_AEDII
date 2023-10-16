typedef struct grafo Grafo;
typedef struct vertice Vertice;
typedef struct aresta Aresta;

Grafo* cria_grafo();

void BuscaCidade(Grafo *gr, char *nome, int id);

void ImprimeGrafo(Grafo *gr);

void imprimeDadosCidade(int i, Grafo* gr);

void liberaGrafo(Grafo *gr);

Grafo *ler_arquivo_arestas_nome(Grafo *gr);

int pegar_vertice(Grafo *gr, char *nome);

Grafo *iniciar_grafo();

Vertice *cria_aresta(Vertice *lista, int v);

Vertice *cria_vertice(int cep, char *cidade_nome);

Grafo* preencheVertices(Grafo *gr);
