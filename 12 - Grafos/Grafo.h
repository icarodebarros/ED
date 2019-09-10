struct grafo {
	int eh_ponderado; // � grafo ponderado? (Se arestas cont�m pesos)
	int nro_vertices; // guarda o n�mero de v�rtices
	int grau_max; // n�mero m�ximo de conex�es de uma v�rtice (limitador do tamanho da lista est�tica)
	int** arestas; // matriz que guarda as conex�es
	float** pesos; // matriz que guarda o peso de cada aresta
	int* grau; // lista que guarda o grau atual de cada v�rtice
};

typedef struct grafo Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo);

int buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado);
int buscaLargura_Grafo(Grafo *gr, int ini, int *visitado);
int menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist);
