typedef struct grafo Grafo;
typedef struct vertice Vertice;
typedef struct aresta Aresta;

Grafo* cria_grafo();

void BuscaCidade(Grafo *gr, char *nome);

void ImprimeGrafo(Grafo *gr);

void imprimeDadosCidade(int i, Grafo* gr);

void liberaGrafo(Grafo *gr);

Grafo *ler_arquivo_arestas_nome(Grafo *gr);

int pegar_vertice(Grafo *gr, char *nome);
