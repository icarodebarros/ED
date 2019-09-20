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
	libera_NO(*raiz); // libera cada nó
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
	Existem 3 principais formas de percorrer uma árvore:
	- Pré-ordem: visita a raiz, o filho da esquerda e o filho da direita;
	- Em-ordem: visita o filho da esquerda, a raiz e o filho da direita;
	- Pós-ordem: visita o filho da esquerda, o filho da direita e a raiz; // usado nos algoritmos libera_ArvBin, altura_ArvBin, totalNO_ArvBin
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
	Árvore binária de busca:
		- É um tipo de árvore binária onde cada nó possui um valor (chave) associado a ele, e esse valor determina a posição do nó na árvore;
		- Não existem valores repetidos;
		- Para cada nó pai:
			* todos os valores da sub-arvore esquerda são menores do que o nó pai;
			* todos os valores da sub-arvore direita são maiores do que o nó pai;
		
	Principais operações:
		- Insersão
			* caso médio: O(log n);
			* Pior caso: O(n) (árvore não balanceada);
		- Remoção
			* Caso médio: O(log n);
			* Pior caso: O(n) (árvore não balanceada);
		- Consulta
			* Caso médio: O(log n);
			* Pior caso: O(n) (árvore não balanceada);
	
	obs.: árvore não balanceada é aquela que tem, por exemplo, muitos nós à esquerda da raiz e apenas 1 à direita da raiz
*/
int insere_ArvBin(ArvBin *raiz, int valor) {
	if (raiz == NULL) return 0;
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if (novo == NULL) return 0;
	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;
	
	if (*raiz == NULL) { // se árvore vazia
		*raiz = novo;
	} else {
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		while (atual != NULL) { // navega nos nós da árvore até chegar num nó folha
			ant = atual;
			if (valor == atual->info) { // elemento já existe
				free(novo);
				return 0;
			}
			if (valor > atual->info) atual = atual->dir;
			else atual = atual->esq;
		}
		// insere como filho do nó folha selecionado
		if (valor > ant->info) ant->dir = novo;
		else ant->esq = novo;
	}
	return 1;
}

/*
	Existem 3 tipos principais de remoção:
		- Nó folha
			* não afeta ninguém;
		- Nó com 1 filho (não importa se esse filho tenha filhos ou não)
			* o pai do nó a ser removido deve apontar para esse nó filho único;
		- Nó com 2 filhos
			* ao se remover um nó com 2 filhos, deve-se buscar na sua sub-arvore esquerda o nó mais à direita. Este é maior
			do que todos os nós da sub-arvore esquerda e menor que todos os nós da sub-arvore direita, ou seja, tem as mesmas
			características do nó que está sendo removido;
		
*/
struct NO* remove_atual(struct NO* atual); // protótipo da função

int remove_ArvBin(ArvBin *raiz, int valor) { // função responsável pela busca do nó a ser removido
	if (raiz == NULL) return 0;
	struct NO* ant = NULL;
	struct NO* atual = *raiz;
	while(atual != NULL) {
		if (valor == atual->info) { // achou o nó a ser removido. Tratar o lado da remoção
			if (atual == *raiz) {
				*raiz = remove_atual(atual);	
			} else {
				if (ant->dir == atual) ant->dir = remove_atual(atual);
				else ant->esq = remove_atual(atual);
			}
			return 1;
		}
		// continua andando na árvore a procura do nó a ser removido
		ant = atual;
		if (valor > atual->info) atual = atual->dir;
		else atual = atual->esq;
	}
	return 0;
}
struct NO* remove_atual(struct NO* atual) { // função responsável por tratar os 3 tipos de remoção
	struct NO *no1, *no2;
	if (atual->esq == NULL) { // se o nó a ser removido não tem filho à esquerda...
		no2 = atual->dir; // ... remove-se o nó e retorna-se o filho da direita (caso esse também  seja nulo não tem problema em retornar null)
		free(atual);
		return no2;
		// Esse if trata os casos de nó folha e nó com 1 filho.
	}
	// Para o caso com 2 filhos...
	no1 = atual;
	no2 = atual->esq;
	while (no2->dir != NULL) { // procura-se o filho mais à direita da sub-arvore esquerda
		no1 = no2;
		no2 = no2->dir;
	}
	
	if (no1 != atual) { // Se existir o nó mais à direita da sub-arvore esquerda, este vai ser substituido pelo nó a ser removido
		no1->dir = no2->esq; // caso o nó mais à direita tenha filho à esquerda, é feita a devida ligação
		no2->esq = atual->esq; // o nó substituto passa ter como filho à esquerda a sub-arvore a qual fazia parte originalmente
	}
	no2->dir = atual->dir; // o nó substituto herda também a sub-arvore direita
	free(atual);
	return no2;
}

/*
	Consulta em uma árvore binária
		- Para um dado valor V:
			* Compara-se com a raiz;
			* Se for menor, é consultada a sub-arvore esquerda;
			* Senão, busca-se na sub-arvore direita;
			* É passivél de recursão, mas sem ela é mais simples;
*/
int consulta_ArvBin(ArvBin *raiz, int valor) { // esse método retorna apenas o status (0 ou 1) se achou o não o valor passado
	if (raiz ==  NULL) return 0;
	struct NO* atual = *raiz;
	while (atual != NULL) {
		if (valor == atual->info) return 1;
		if (valor > atual->info) atual = atual->dir;
		else atual = atual->esq;
	}
	return 0;
}
