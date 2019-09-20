#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

struct NO {
	int info;
	int alt; // altura daquela sub-arvore
	struct NO *esq;
	struct NO *dir;
};

// ------------ Funções auxiliares:
int altura_NO(struct NO* no) { // calcula a altura do nó
	return (no == NULL) ? -1 : no->alt;
}

int fatorBalanceamento_NO(struct NO* no) { // calcula o fator de balanceamento de um nó
	return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y) {
	return (x > y) ? x : y;
}

/*
	Rotação: Operação básica de balanceamento de uma Árvore AVL
	
	Rotação Simples:
		- quando o nó inserido (causador do desbalanceamento) está no mesmo sentido da inclinação
		- ex.: A    o nó C é inserido na sub-árvore direita da sub-árvore direita de A
				\
				 B
				  \
				   C
	
	Rotação Dupla:
		- o nó inserido está inclinado no sentido inverso ao pai
		- equivalente a duas rotações simples
		- ex.: A    o nó C é inserido na sub-árvore esquerda da sub-árvore direita de A
				\
				 B
				/ 
			   C
	
	Rotação RR: rotação simples à esquerda; (usado para resolver o exemplo de rotação simples acima)
	Rotação LL: rotação simples à direita;
	Rotação RL: rotação dupla à esquerda; (usado para resolver o exemplo de rotação dupla acima)
	Rotação LR: rotação dupla à direita;
	ex.: RL = LL + RR; <- equivale à duas rotações simples
	
	Quando usar cada rotação:
		- se o fator de balanceamento for:
			* A=+2 e B=+1 -> rotação LL;
			* A=-2 e B=-1 -> rotação RR;
			* A=+2 e B=-1 -> rotação LR;
			* A=-2 e B=+1 -> rotação RL;
			
	Implementação de rotações:
		- as rotações são aplicadas no ancestral mais próximo do nó inserido cujo fator de balanceamento passa a ser +-2
		- ex.:	O fb=-3
			   / \
		fb=0  O   O fb=-2   <<<<< ancestral alvo das rotações
			  	   \
			  	    O fb=+1
			  	   /
			  	  O fb=0    <<<< nó inserido
		
*/

void RotacaoLL(ArvAVL *raiz) { // OBS.: a "raiz" é o nó desbalanceado!!!! (fb=+-2)
	struct NO *no;
	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = *raiz;
	(*raiz)->alt = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
	no->alt = maior(altura_NO(no->esq), (*raiz)->alt) + 1;
	*raiz = no;
}

void RotacaoRR(ArvAVL *raiz) {
	struct NO *no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = *raiz;
	(*raiz)->alt = maior(altura_NO((*raiz)->esq), altura_NO((*raiz)->dir)) + 1;
	no->alt = maior(altura_NO(no->dir), (*raiz)->alt) + 1;
	*raiz = no;
}

void RotacaoLR(ArvAVL *raiz) {
	RotacaoRR(&(*raiz)->esq);
	RotacaoLL(raiz);
}

void RotacaoRL(ArvAVL *raiz) {
	RotacaoLL(&(*raiz)->dir);
	RotacaoRR(raiz);
}

// --------------------------------

ArvAVL* cria_arvore() {
	ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
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

void libera_ArvAVL(ArvAVL *raiz) {
	if (raiz == NULL) return;
	libera_NO(*raiz); // libera cada nó
	free(raiz); // libera a raiz
}

int estaVazia_ArvAVL(ArvAVL *raiz) {
	if (raiz == NULL || *raiz == NULL) return 1;
	return 0;
}

int altura_ArvAVL(ArvAVL *raiz) {
	if (raiz == NULL || *raiz == NULL) return 0;
	int alt_esq = altura_ArvAVL(&((*raiz)->esq));
	int alt_dir = altura_ArvAVL(&((*raiz)->dir));
	if (alt_esq > alt_dir) return (alt_esq + 1);
	return (alt_dir + 1);
}

int totalNO_ArvAVL(ArvAVL *raiz) {
	if (raiz == NULL || *raiz == NULL) return 0;
	int totalNO_esq = totalNO_ArvAVL(&((*raiz)->esq));
	int totalNO_dir = totalNO_ArvAVL(&((*raiz)->dir));
	return(totalNO_esq + totalNO_dir + 1);
}

/*
	Existem 3 principais formas de percorrer uma árvore:
	- Pré-ordem: visita a raiz, o filho da esquerda e o filho da direita;
	- Em-ordem: visita o filho da esquerda, a raiz e o filho da direita;
	- Pós-ordem: visita o filho da esquerda, o filho da direita e a raiz; // usado nos algoritmos libera_ArvAVL, altura_ArvAVL, totalNO_ArvAVL
*/

void preOrdem_ArvAVL(ArvAVL *raiz) {
	if (raiz == NULL || *raiz == NULL) return;
	printf("%d\n", (*raiz)->info);
	preOrdem_ArvAVL(&((*raiz)->esq));
	preOrdem_ArvAVL(&((*raiz)->dir));
}

void emOrdem_ArvAVL(ArvAVL *raiz) {
	if (raiz == NULL || *raiz == NULL) return;
	emOrdem_ArvAVL(&((*raiz)->esq));
	printf("%d\n", (*raiz)->info);
	emOrdem_ArvAVL(&((*raiz)->dir));
}

void posOrdem_ArvAVL(ArvAVL *raiz) {
	if (raiz == NULL || *raiz == NULL) return;
	posOrdem_ArvAVL(&((*raiz)->esq));
	posOrdem_ArvAVL(&((*raiz)->dir));
	printf("%d\n", (*raiz)->info);
}

/*
	Após a insersão padrão:
		- calcula-se as alturas de cada sub-arvore;
		- faz-se a rotação necessária cajo haja desbalanceamento;
*/
int insere_ArvAVL(ArvAVL *raiz, int valor) {
	int res;
	if (*raiz == NULL) {
		struct NO* novo;
		novo = (struct NO*) malloc(sizeof(struct NO));
		if (novo == NULL) return 0;
		novo->info = valor;
		novo->alt = 0;
		novo->dir = NULL;
		novo->esq = NULL;
		*raiz = novo;
		return 1;
	}
	
	struct NO *atual = *raiz;
	if (valor < atual->info) {
		if ((res = insere_ArvAVL(&(atual->esq), valor)) == 1) {
			if(fatorBalanceamento_NO(atual) >= 2) {
				if (valor < (*raiz)->esq->info) RotacaoLL(raiz);
				else RotacaoLR(raiz);				
			}
		}
	} else {
		if (valor > atual->info) {
			if ((res = insere_ArvAVL(&(atual->dir), valor)) == 1) {
				if (fatorBalanceamento_NO(atual) >=2) {
					if ((*raiz)->dir->info < valor) RotacaoRR(raiz);
					else RotacaoRL(raiz);
				}
			}
		} else { // caso o valor a ser inserido ja exista
			printf("Valor duplicado!\n");
			return 0;
		}
	}
	atual->alt = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;
	
	return res;
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
struct NO* procuraMenor(struct NO* atual); // protótipo da função

int remove_ArvAVL(ArvAVL *raiz, int valor) { // função responsável pela busca do nó a ser removido
	if (*raiz == NULL) {
		printf("valor nao existe!\n");
		return 0;	
	}
	int res;
	if (valor < (*raiz)->info) {
		if ((res = remove_ArvAVL(&((*raiz)->esq), valor)) == 1) {
			if(fatorBalanceamento_NO(*raiz) >= 2) {
				if (altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir)) RotacaoRR(raiz);
				else RotacaoRL(raiz);				
			}
		}
	}
	if (valor > (*raiz)->info) {
		if ((res = remove_ArvAVL(&((*raiz)->dir), valor)) == 1) {
			if(fatorBalanceamento_NO(*raiz) >= 2) {
				if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq)) RotacaoLL(raiz);
				else RotacaoLR(raiz);				
			}
		}
	}
	if (valor == (*raiz)->info) { // achou nó a ser removido
		if (((*raiz)->esq == NULL || (*raiz)->dir == NULL)) { // trata se o nó a ser removido tem 1 ou nenhum filho
			struct NO *oldNode = (*raiz);
			if ((*raiz)->esq != NULL) *raiz = (*raiz)->esq;
			else *raiz = (*raiz)->dir;
			free(oldNode);
		} else { // trata caso com 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir); // busca o menor valor da sub-arvore com 'maiores' valores para substituição
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, temp->info); // remove o nó da substituição pois agora ele está no lugar do nó removido
			if (fatorBalanceamento_NO(*raiz) >=2 ) {
				if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq)) RotacaoLL(raiz);
				else RotacaoLR(raiz);
			}
		}
		return 1;
	}
	
	return res;
}
struct NO* procuraMenor(struct NO* atual) { // procura o nó mais a esquerda
	struct NO *no1 = atual;
	struct NO *no2 = atual->esq;
	while(no2 != NULL) {
		no1 = no2;
		no2 = no2->esq;
	}
	return no1;
}

/*
	Consulta em uma árvore binária
		- Para um dado valor V:
			* Compara-se com a raiz;
			* Se for menor, é consultada a sub-arvore esquerda;
			* Senão, busca-se na sub-arvore direita;
			* É passivél de recursão, mas sem ela é mais simples;
*/
int consulta_ArvAVL(ArvAVL *raiz, int valor) { // esse método retorna apenas o status (0 ou 1) se achou o não o valor passado
	if (raiz ==  NULL) return 0;
	struct NO* atual = *raiz;
	while (atual != NULL) {
		if (valor == atual->info) return 1;
		if (valor > atual->info) atual = atual->dir;
		else atual = atual->esq;
	}
	return 0;
}
