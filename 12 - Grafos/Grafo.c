#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado) { // gera grafo de Lista de Adjac�ncia 
	Grafo *gr = (Grafo*) malloc(sizeof(struct grafo));
	if (gr != NULL) {
		int i;
		gr->nro_vertices = nro_vertices;
		gr->grau_max = grau_max;
		gr->eh_ponderado = (eh_ponderado != 0) ? 1 : 0;
		gr->grau = (int*) calloc(nro_vertices, sizeof(int)); // fun��o calloc pra alocar com valor 0, pq inicialmente cada v�rtice tem grau 0;
		gr->arestas = (int**) malloc(nro_vertices * sizeof(int*)); // Matriz de arestas (lista + sub-listas)
		for (i = 0; i < nro_vertices; i++) { // Pra cada v�rtice � gerado sua sub-lista de conex�es
			gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));
			if(gr->eh_ponderado) { // Se for ponderado � gerado uma nova matriz guardando os pesos
				gr->pesos = (float**) malloc(nro_vertices * sizeof(float*));
				for(i = 0; i < nro_vertices; i++) {
					gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
				}
			}
		}
	}
	
	return gr;
}

void libera_Grafo(Grafo* gr) {
	if (gr != NULL) {
		int i;
		for(i = 0; i < gr->nro_vertices; i++) free(gr->arestas[i]);
		free(gr->arestas);
		
		if(gr->eh_ponderado) {
			for(i = 0; i < gr->nro_vertices; i++) free(gr->pesos[i]);
			free(gr->pesos);	
		}
		free(gr->grau);
		free(gr);
	}
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso) {
	// eh_digrafo: grafo d�grafo � aquele cujam as arestas tem sentido �nico
	if (gr == NULL || orig < 0 || orig >= gr->nro_vertices || dest < 0 || dest >= gr->nro_vertices) return 0;
	
	gr->arestas[orig][gr->grau[orig]] = dest; // cria a aresta origem-destino
	if (gr->eh_ponderado) gr->pesos[orig][gr->grau[orig]] = peso; // guarda o peso na metriz de pesos
	gr->grau[orig]++;
	
	if (eh_digrafo == 0) insereAresta(gr, dest, orig, 1, peso); // Caso n�o seja d�grafo, chama-se a recurs�o para criar aresta inversa
	
	return 1;
}

int removeAresta(Grafo* gr, int orig, int dest, int eh_digrafo) {
	if (gr == NULL || orig < 0 || orig >= gr->nro_vertices || dest < 0 || dest >= gr->nro_vertices) return 0;
	
	int i = 0;
	while(i < gr->grau[orig] && gr->arestas[orig][i] != dest) i++;
	if (i == gr->grau[orig]) return 0; // elemento n�o encontrado
	
	gr->grau[orig]--; // reduz o graum ja que a aresta vai ser removida
	gr->arestas[orig][i] = gr->arestas[orig][gr->grau[orig]]; // a aresta O-D � sobrescrita com a aresta O-ultimoD
	
	if (gr->eh_ponderado) gr->pesos[orig][i] = gr->pesos[orig][gr->grau[orig]]; // faz-se a mesma coisa com o peso da aresta sobrescrita
	
	if (eh_digrafo == 0) removeAresta(gr, dest, orig, 1); // Caso n�o seja d�grafo, chama-se a recurs�o para remover aresta inversa

	return 1;	
}

// --------------------------------------------------------------------------------
void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont) { // Fun��o auxiliar que calcula a busca
	int i;
	visitado[ini] = cont;
	for(i = 0; i < gr->grau[ini]; i++) {
		if (!visitado[gr->arestas[ini][i]]) {
			buscaProfundidade(gr, gr->arestas[ini][i], visitado, cont+1); // Faz a busca para cada vizinho n�o visitado da aresta em quest�o
		}
	}
}

int buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado) { // Fun��o principal que faz a interface com o usu�rio
	int i, cont = 1;
	for (i = 0; i < gr->nro_vertices; i++) visitado[i] = 0; // marca todos os v�rtices como N�O visitados
	buscaProfundidade(gr, ini, visitado, cont);
}
// --------------------------------------------------------------------------------
int buscaLargura_Grafo(Grafo *gr, int ini, int *visitado) {
	int i, vert, NV, cont = 1, *fila, IF = 0, FF = 0; // NV = n�mero de v�rtices, IF = in�cio da fila, FF = final da fila
	for (i = 0; i < gr->nro_vertices; i++) visitado[i] = 0;
	NV = gr->nro_vertices;
	fila = (int*) malloc(NV * sizeof(int));
	FF++;
	fila[FF] = ini;
	visitado[ini] = cont;
	while(IF != FF) { // enquanto fila n�o for vazia
		IF = (IF + 1) % NV;
		vert = fila[IF]; // recupera o in�cio da fila
		cont++;
		for (i = 0; i < gr->grau[vert]; i++) { // visita todos os vizinhos de vert
			if (!visitado[gr->arestas[vert][i]]) {
				FF = (FF + 1) % NV;
				fila[FF] = gr->arestas[vert][i];
				visitado[gr->arestas[vert][i]] = cont;
			}
		}
	}
	free(fila);
}
// --------------------------------------------------------------------------------
int procuraMenorDistancia(float *dist, int *visitado, int NV) { // Func aux que busca o v�rtice com menor dist�ncia e q n�o tenha sido visitado ainda
	// dist = vetor que guarda as dist�ncias at� a refer�ncia (v�rtices n�o visitados tem dist�ncia -1)
	// visitado = vetor que guarda os v�rtices j� visitados (inicialmente o array � todo preenchido com zeros)
	int i, menor = -1, primeiro = 1;
	for (i = 0; i < NV; i++) {
		if (dist[i] >= 0 && visitado[i] == 0) {
			if (primeiro) {
				menor = i;
				primeiro = 0;
			} else {
				if (dist[menor] > dist[i]) menor = i;
			}
		}
	}
	return menor;
}
int menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist) {
	int i, cont, NV, ind, *visitado, u;
	cont = NV = gr->nro_vertices; // contador p garantir que se visitou todos os v�rtices
	visitado = (int*) malloc(NV * sizeof(int));
	for (i = 0; i < NV; i++) { // inicializa vetores
		ant[i] = -1;
		dist[i] = -1;
		visitado[i] = 0;
	}
	dist[ini] = 0;
	while(cont > 0) { // procura v�rtice com menor dist�ncia (de ini) e marca como visitado
		u = procuraMenorDistancia(dist, visitado, NV);
		if (u == -1) break; // caso n�o exista caminho entre todos os v�rtices (grafo disconexo)
		visitado[u] = 1;
		cont--;
		for (i = 0; i < gr->grau[u]; i++) { // pra cada v�rtice visinho atualiza-se a dist�ncia
			ind = gr->arestas[u][i];
			if (dist[ind] < 0) {
				dist[ind] = dist[u] + 1; // ou peso da aresta: dist[ind] = dist[u] + gr->pesos[u][i];
				ant[ind] = u;
			} else {
				if (dist[ind] > dist[u] + 1) { // ou peso da aresta: if (dist[ind] > dist[u] + 1)
					dist[ind] = dist[u] + 1; // ou peso da aresta: dist[ind] = dist[u] + gr->pesos[u][i];
					ant[ind] = u;
				}
			}
		}
	}
	free(visitado);
}
