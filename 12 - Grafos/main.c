#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/* 
	Maneiras de representar grafos na computa��o:
		* Matriz de Adjac�ncia (Em geral quando se tem grafos muito conectados)
			- Matriz NxN, onde N � o n�mero de v�rtices;
			- Alato custo computacional, O(N^2);
			- Aresta � representada por uma "marca" na posi��o (i, j) da matriz (aresta que liga o v�rtice i ao j);
			
		* Lista de Adjac�ncia (Em geral quando se tem grafos espa�ados)
			- Lista de tamanho N, onde N � o n�mero de v�rtices;
			- Cada elemento da lista � o cabe�alho de uma sub-lista, onde essa cont�m os elementos que o v�rtice do cabe�alho se liga;
	
	OBS.: ver imagens da pasta
	
	
	Principais buscas em grafos:
		* Busca em profundidade
			- Partindo de um v�rtice inicial, ela explora o m�ximo poss�vel cada um dos seus ramos antes de retroceder ("backtracking");
			- Pode ser usado para: encontrar componentes fortemente conectados, ordena��o topol�gica do grafo, resolver quebra-cabecas (Ex.: labirinto);
			
		* Busca em largura
			- Partindo de um v�rtice inicial, ela explora todos os v�rtices vizinhos. Em seguida, para cada v�rtice vizinho, ela repete esse
			processo, visitando os v�rtices ainda inexplorados;
			- Pode ser usado para: achar componentes conectados, achar todos os v�rtices conectados a apenas 1 componente, achar o menor
			caminho entre dois v�rtices, testar biparti��o em grafos;
			
		* Busca pelo menor caminho
			- Partindo de um v�rtice inicial, calcula a menor dist�ncia desse v�rtice a todos os demais (desde que exista um caminho entre eles);
			- Algoritmo de Dijkstra: resolve esse problema para grafos "dirigido" (digrafo) ou "n�o dirigido" (grafo) com arestas de peso "n�o negativo";
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

	int ant[5]; // vetor que guarda arestas anteriores �s dos indices na busca do menor caminho;
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
