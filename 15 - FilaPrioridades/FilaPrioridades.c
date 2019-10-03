#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPrioridades.h"

#define MAX 100
struct paciente {
    char nome[30];
    int prio;
};

struct fila_prioridade {
    int qtd;
    struct paciente dados[MAX];
};

FilaPrio* cria_FilaPrio() {
    FilaPrio *fp;
    fp = (FilaPrio*) malloc(sizeof(struct paciente));
    if (fp != NULL)
        fp->qtd = 0;
    return fp;
}

void libera_FilaPrio(FilaPrio* fp) {
    free(fp);
}

int tamanho_FilaPrio(FilaPrio* fp) {
    return (fp == NULL) ? -1 : fp->qtd; // (*fp).qtd
}

int estaCheia_FilaPrio(FilaPrio* fp) {
    return (fp == NULL) ? -1 : (fp->qtd == MAX);
}

int estaVazia_FilaPrio(FilaPrio* fp) {
    return (fp == NULL) ? -1 : (fp->qtd == 0);
}

/*
	Fila de prioridade usando um array ordenado:
	 - os elementos s�o ordenados de forma crescente no array;
	 - o elemento de maior prioridade estar� no final do array (inicio da fila);
	 - o elemento de menor prioridade estar� no inicio do array (final da fila);
*/
int insere_FilaPrio(FilaPrio* fp, char *nome, int prio) {
    if (fp == NULL || estaCheia_FilaPrio(fp)) return 0;
    int i = fp->qtd - 1;
    while(i >= 0 && fp->dados[i].prio >= prio) {
    	fp->dados[i+1] = fp->dados[i];
    	i--;
	}
	strcpy(fp->dados[i+1].nome, nome);
    fp->dados[i+1].prio = prio;
    fp->qtd++;
    return 1;
}

int remove_FilaPrio(FilaPrio* fp) { // remove do fim (elemento de maior prioridade)
    if (fp == NULL || fp->qtd == 0) return 0;
    fp->qtd--;
    return 1;
}

int consulta_FilaPrio(FilaPrio* fp, char *nome) { // consulta sempre pelo fim
    if (fp == NULL || fp->qtd == 0) return 0;
    strcpy(nome, fp->dados[fp->qtd-1].nome);
    return 1;
}

// ------------------------------------------------------------------------------------
/*
	Fila de prioridade usando HEAP BIN�RIA
		- Uma heap permite simular uma �rvore bin�ria completa ou quase completa (exceto seu �ltimo n�vel);
		- Cada osi��o do array passa a ser considerado a 'pai' de duas outras posi��es, chamadas 'filhos';
		- Posi��o 'i' passa a ser pai de:
			* '2*i+1' (filho da esquerda);
			* '2*i+2' (filho da direita);
		- Os elementos s�o dispostos na heap de forma que um pai tem sempre uma prioridade maior ou igual � prioridade de seus filhos;
		- Custo:
			* Inser��o O(logN);
			* Remo��o O(logN);
			* Em ampas precisamos verificar e corrigir viola��es de prioridades de heap;
			
		-Ex.:
	�rvore:    8		Array: [8, 6, 4, 1, 5, 2]
			  / \
			 6   4
		   / \  / 
		  1  5 2
*/
void promoverElemento(FilaPrio* fp, int filho); // prot�tipo

int insere_FilaPrio2(FilaPrio* fp, char* nome, int prio) {
    if (fp == NULL || fp->qtd == MAX) return 0;
	strcpy(fp->dados[fp->qtd].nome, nome);
    fp->dados[fp->qtd].prio = prio;
    promoverElemento(fp, fp->qtd);
    fp->qtd++;
    return 1;
}

void promoverElemento(FilaPrio* fp, int filho) { // int filho � a posi��o que o elemento acabou de ser inserido
	int pai;
	struct paciente temp;
	pai = (filho - 1) / 2; // calcula posi��o do pai do elemento inserido
	while((filho > 0) && (fp->dados[pai].prio <= fp->dados[filho].prio)) { // inverte pai/filho caso necess�rio at� �rvore organizada
		temp = fp->dados[filho];
		fp->dados[filho] = fp->dados[pai];
		fp->dados[pai] = temp;
		filho = pai;
		pai = (pai - 1) / 2;
	}
}

/*
	Remo��o:
		- Remover o elemento que est� no topo da heap (in�cio do array);
		- Para ocupar a posi�o vaga, coloca-se o elemento do final do array no in�cio (desordenando a heap);
		- Move-se esse novo elemento raiz para sua correta posi��o de prioridade;		
*/
void rebaixarElemento(FilaPrio* fp, int pai); // prot�tipo

int remove_FilaPrio2(FilaPrio* fp) {
	if (fp == NULL || fp->qtd == 0) return 0;
	fp->qtd--;
	fp->dados[0] = fp->dados[fp->qtd];
	rebaixarElemento(fp, 0);
	return 1;
}

void rebaixarElemento(FilaPrio* fp, int pai) {
	struct paciente temp;
	int filho = 2 * pai + 1;
	while(filho < fp->qtd-1) {
		if ((filho < fp->qtd-1) && (fp->dados[filho].prio < fp->dados[filho+1].prio)) filho++; // Se o filho tem irm�o && quem � o maior
		if (fp->dados[pai].prio >= fp->dados[filho].prio) break; // Pai >= filho?
		// faz a troca pai/filho
		temp = fp->dados[pai];
		fp->dados[pai] = fp->dados[filho];
		fp->dados[filho] = temp;
		// calcula novo filho
		pai = filho;
		filho = 2 * pai + 1;
	}
}

/*
	Consulta:
		- Na consulta, a raiz da heap � o elemento de maior prioridade
*/
int consulta_FilaPrio2(FilaPrio* fp, char* nome) {
	if (fp == NULL || fp->qtd == 0) return 0;
	strcpy(nome, fp->dados[0].nome);
	return 1;
}
