#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/* 
	Maneiras de representar grafos na computação:
		* Matriz de Adjacência (Em geral quando se tem grafos muito conectados)
			- Matriz NxN, onde N é o número de vértices;
			- Alato custo computacional, O(N^2);
			- Aresta é representada por uma "marca" na posição (i, j) da matriz (aresta que liga o vértice i ao j);
			
		* Lista de Adjacência (Em geral quando se tem grafos espaçados)
			- Lista de tamanho N, onde N é o número de vértices;
			- Cada elemento da lista é o cabeçalho de uma sub-lista, onde essa contém os elementos que o vértice do cabeçalho se liga;
	
	OBS.: ver imagens da pasta
	
	
	Principais buscas em grafos:
		* Busca em profundidade
			- Partindo de um vértice inicial, ela explora o máximo possível cada um dos seus ramos antes de retroceder ("backtracking");
			- Pode ser usado para: encontrar componentes fortemente conectados, ordenação topológica do grafo, resolver quebra-cabecas (Ex.: labirinto);
			
		* Busca em largura
			- Partindo de um vértice inicial, ela explora todos os vértices vizinhos. Em seguida, para cada vértice vizinho, ela repete esse
			processo, visitando os vértices ainda inexplorados;
			- Pode ser usado para: achar componentes conectados, achar todos os vértices conectados a apenas 1 componente, achar o menor
			caminho entre dois vértices, testar bipartição em grafos;
			
		* Busca pelo menor caminho
			- Partindo de um vértice inicial, calcula a menor distância desse vértice a todos os demais (desde que exista um caminho entre eles);
			- Algoritmo de Dijkstra: resolve esse problema para grafos "dirigido" (digrafo) ou "não dirigido" (grafo) com arestas de peso "não negativo";
 */

int main(int argc, char *argv[]) {
	
	int i, j, eh_digrafo = 1;
	Grafo *gr = cria_Grafo(5, 5, 0);
	insereAresta(gr, 0, 1, eh_digrafo, 0);
	insereAresta(gr, 1, 3, eh_digrafo, 0);
	insereAresta(gr, 1, 2, eh_digrafo, 0);
	insereAresta(gr, 2, 4, eh_digrafo, 0);
	insereAresta(gr, 3, 0, eh_digrafo, 0);
	insereAresta(gr, 3, 4, eh_digrafo, 0);
	insereAresta(gr, 4, 1, eh_digrafo, 0);
	
	printf("Grafo:\n");
	for (i = 0; i < gr->nro_vertices; i++) {
		printf("%d: ", i);
		for (j = 0; j < gr->grau[i]; j++) {
			printf("%d ", gr->arestas[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	int vis[5]; // vetor que guarda arestas visitadas
	buscaProfundidade_Grafo(gr, 0, vis);
//	buscaLargura_Grafo(gr, 0, vis);

//	printf("Vetor 'visitado':\n");
//	for (i = 0; i < 5; i++) {
//		printf("%d: %d\n", i, vis[i]);
//	}
//	printf("\n");

	int ant[5]; // vetor que guarda arestas anteriores às dos indices na busca do menor caminho;
	float dist[5];
	menorCaminho_Grafo(gr, 0, ant, dist);
	
	printf("Vetor 'ant':\n");
	for (i = 0; i < 5; i++) {
		printf("%d: %d\n", i, ant[i]);
	}
	printf("\n");
	printf("Vetor 'dist':\n");
	for (i = 0; i < 5; i++) {
		printf("%d: %f\n", i, dist[i]);
	}
	printf("\n");
	
//	removeAresta(gr, 0, 1, 0);

	libera_Grafo(gr);
	
	system("pause");
	return 0;
}
