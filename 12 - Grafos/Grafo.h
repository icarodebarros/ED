struct grafo {
	int eh_ponderado; // é grafo ponderado? (Se arestas contém pesos)
	int nro_vertices; // guarda o número de vértices
	int grau_max; // número máximo de conexões de uma vértice (limitador do tamanho da lista estática)
	int** arestas; // matriz que guarda as conexões
	float** pesos; // matriz que guarda o peso de cada aresta
	int* grau; // lista que guarda o grau atual de cada vértice
};

typedef struct grafo Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);

int buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado);
int buscaLargura_Grafo(Grafo *gr, int ini, int *visitado);
int menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist);
