#include <stdio.h>
#include <stdlib.h>
#include "Arvore.h"

struct NO {
	int info;
	struct NO *esq;
	struct NO *dir;
};

ArvBin* cria_arvore() {
	ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
	if (raiz != NULL) *raiz = NULL;
	return raiz;
}

void libera_NO(struct NO* no) {
	if (no == NULL) return;
	libera_NO(no->esq);
	libera_NO(no->dir);
	free(no);
	no = NULL;
}

void libera_ArvBin(ArvBin *raiz) {
	if (raiz == NULL) return;
	libera_NO(*raiz); // libera cada n�
	free(raiz); // libera a raiz
}

int estaVazia_ArvBin(ArvBin *raiz) {
	if (raiz == NULL || *raiz == NULL) return 1;
	return 0;
}

int altura_ArvBin(ArvBin *raiz) {
	if (raiz == NULL || *raiz == NULL) return 0;
	int alt_esq = altura_ArvBin(&((*raiz)->esq));
	int alt_dir = altura_ArvBin(&((*raiz)->dir));
	if (alt_esq > alt_dir) return (alt_esq + 1);
	return (alt_dir + 1);
}

int totalNO_ArvBin(ArvBin *raiz) {
	if (raiz == NULL || *raiz == NULL) return 0;
	int totalNO_esq = totalNO_ArvBin(&((*raiz)->esq));
	int totalNO_dir = totalNO_ArvBin(&((*raiz)->dir));
	return(totalNO_esq + totalNO_dir + 1);
}

/*
	Existem 3 principais formas de percorrer uma �rvore:
	- Pr�-ordem: visita a raiz, o filho da esquerda e o filho da direita;
	- Em-ordem: visita o filho da esquerda, a raiz e o filho da direita;
	- P�s-ordem: visita o filho da esquerda, o filho da direita e a raiz; // usado nos algoritmos libera_ArvBin, altura_ArvBin, totalNO_ArvBin
*/

void preOrdem_ArvBin(ArvBin *raiz) {
	if (raiz == NULL || *raiz == NULL) return;
	printf("%d\n", (*raiz)->info);
	preOrdem_ArvBin(&((*raiz)->esq));
	preOrdem_ArvBin(&((*raiz)->dir));
}

void emOrdem_ArvBin(ArvBin *raiz) {
	if (raiz == NULL || *raiz == NULL) return;
	emOrdem_ArvBin(&((*raiz)->esq));
	printf("%d\n", (*raiz)->info);
	emOrdem_ArvBin(&((*raiz)->dir));
}

void posOrdem_ArvBin(ArvBin *raiz) {
	if (raiz == NULL || *raiz == NULL) return;
	posOrdem_ArvBin(&((*raiz)->esq));
	posOrdem_ArvBin(&((*raiz)->dir));
	printf("%d\n", (*raiz)->info);
}

/*
	�rvore bin�ria de busca:
		- � um tipo de �rvore bin�ria onde cada n� possui um valor (chave) associado a ele, e esse valor determina a posi��o do n� na �rvore;
		- N�o existem valores repetidos;
		- Para cada n� pai:
			* todos os valores da sub-arvore esquerda s�o menores do que o n� pai;
			* todos os valores da sub-arvore direita s�o maiores do que o n� pai;
		
	Principais opera��es:
		- Insers�o
			* caso m�dio: O(log n);
			* Pior caso: O(n) (�rvore n�o balanceada);
		- Remo��o
			* Caso m�dio: O(log n);
			* Pior caso: O(n) (�rvore n�o balanceada);
		- Consulta
			* Caso m�dio: O(log n);
			* Pior caso: O(n) (�rvore n�o balanceada);
	
	obs.: �rvore n�o balanceada � aquela que tem, por exemplo, muitos n�s � esquerda da raiz e apenas 1 � direita da raiz
*/
int insere_ArvBin(ArvBin *raiz, int valor) {
	if (raiz == NULL) return 0;
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if (novo == NULL) return 0;
	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;
	
	if (*raiz == NULL) { // se �rvore vazia
		*raiz = novo;
	} else {
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		while (atual != NULL) { // navega nos n�s da �rvore at� chegar num n� folha
			ant = atual;
			if (valor == atual->info) { // elemento j� existe
				free(novo);
				return 0;
			}
			if (valor > atual->info) atual = atual->dir;
			else atual = atual->esq;
		}
		// insere como filho do n� folha selecionado
		if (valor > ant->info) ant->dir = novo;
		else ant->esq = novo;
	}
	return 1;
}

/*
	Existem 3 tipos principais de remo��o:
		- N� folha
			* n�o afeta ningu�m;
		- N� com 1 filho (n�o importa se esse filho tenha filhos ou n�o)
			* o pai do n� a ser removido deve apontar para esse n� filho �nico;
		- N� com 2 filhos
			* ao se remover um n� com 2 filhos, deve-se buscar na sua sub-arvore esquerda o n� mais � direita. Este � maior
			do que todos os n�s da sub-arvore esquerda e menor que todos os n�s da sub-arvore direita, ou seja, tem as mesmas
			caracter�sticas do n� que est� sendo removido;
		
*/
struct NO* remove_atual(struct NO* atual); // prot�tipo da fun��o

int remove_ArvBin(ArvBin *raiz, int valor) { // fun��o respons�vel pela busca do n� a ser removido
	if (raiz == NULL) return 0;
	struct NO* ant = NULL;
	struct NO* atual = *raiz;
	while(atual != NULL) {
		if (valor == atual->info) { // achou o n� a ser removido. Tratar o lado da remo��o
			if (atual == *raiz) {
				*raiz = remove_atual(atual);	
			} else {
				if (ant->dir == atual) ant->dir = remove_atual(atual);
				else ant->esq = remove_atual(atual);
			}
			return 1;
		}
		// continua andando na �rvore a procura do n� a ser removido
		ant = atual;
		if (valor > atual->info) atual = atual->dir;
		else atual = atual->esq;
	}
	return 0;
}
struct NO* remove_atual(struct NO* atual) { // fun��o respons�vel por tratar os 3 tipos de remo��o
	struct NO *no1, *no2;
	if (atual->esq == NULL) { // se o n� a ser removido n�o tem filho � esquerda...
		no2 = atual->dir; // ... remove-se o n� e retorna-se o filho da direita (caso esse tamb�m  seja nulo n�o tem problema em retornar null)
		free(atual);
		return no2;
		// Esse if trata os casos de n� folha e n� com 1 filho.
	}
	// Para o caso com 2 filhos...
	no1 = atual;
	no2 = atual->esq;
	while (no2->dir != NULL) { // procura-se o filho mais � direita da sub-arvore esquerda
		no1 = no2;
		no2 = no2->dir;
	}
	
	if (no1 != atual) { // Se existir o n� mais � direita da sub-arvore esquerda, este vai ser substituido pelo n� a ser removido
		no1->dir = no2->esq; // caso o n� mais � direita tenha filho � esquerda, � feita a devida liga��o
		no2->esq = atual->esq; // o n� substituto passa ter como filho � esquerda a sub-arvore a qual fazia parte originalmente
	}
	no2->dir = atual->dir; // o n� substituto herda tamb�m a sub-arvore direita
	free(atual);
	return no2;
}

/*
	Consulta em uma �rvore bin�ria
		- Para um dado valor V:
			* Compara-se com a raiz;
			* Se for menor, � consultada a sub-arvore esquerda;
			* Sen�o, busca-se na sub-arvore direita;
			* � passiv�l de recurs�o, mas sem ela � mais simples;
*/
int consulta_ArvBin(ArvBin *raiz, int valor) { // esse m�todo retorna apenas o status (0 ou 1) se achou o n�o o valor passado
	if (raiz ==  NULL) return 0;
	struct NO* atual = *raiz;
	while (atual != NULL) {
		if (valor == atual->info) return 1;
		if (valor > atual->info) atual = atual->dir;
		else atual = atual->esq;
	}
	return 0;
}
