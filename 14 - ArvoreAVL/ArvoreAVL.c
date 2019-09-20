#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

struct NO {
	int info;
	int alt; // altura daquela sub-arvore
	struct NO *esq;
	struct NO *dir;
};

// ------------ Fun��es auxiliares:
int altura_NO(struct NO* no) { // calcula a altura do n�
	return (no == NULL) ? -1 : no->alt;
}

int fatorBalanceamento_NO(struct NO* no) { // calcula o fator de balanceamento de um n�
	return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y) {
	return (x > y) ? x : y;
}

/*
	Rota��o: Opera��o b�sica de balanceamento de uma �rvore AVL
	
	Rota��o Simples:
		- quando o n� inserido (causador do desbalanceamento) est� no mesmo sentido da inclina��o
		- ex.: A    o n� C � inserido na sub-�rvore direita da sub-�rvore direita de A
				\
				 B
				  \
				   C
	
	Rota��o Dupla:
		- o n� inserido est� inclinado no sentido inverso ao pai
		- equivalente a duas rota��es simples
		- ex.: A    o n� C � inserido na sub-�rvore esquerda da sub-�rvore direita de A
				\
				 B
				/ 
			   C
	
	Rota��o RR: rota��o simples � esquerda; (usado para resolver o exemplo de rota��o simples acima)
	Rota��o LL: rota��o simples � direita;
	Rota��o RL: rota��o dupla � esquerda; (usado para resolver o exemplo de rota��o dupla acima)
	Rota��o LR: rota��o dupla � direita;
	ex.: RL = LL + RR; <- equivale � duas rota��es simples
	
	Quando usar cada rota��o:
		- se o fator de balanceamento for:
			* A=+2 e B=+1 -> rota��o LL;
			* A=-2 e B=-1 -> rota��o RR;
			* A=+2 e B=-1 -> rota��o LR;
			* A=-2 e B=+1 -> rota��o RL;
			
	Implementa��o de rota��es:
		- as rota��es s�o aplicadas no ancestral mais pr�ximo do n� inserido cujo fator de balanceamento passa a ser +-2
		- ex.:	O fb=-3
			   / \
		fb=0  O   O fb=-2   <<<<< ancestral alvo das rota��es
			  	   \
			  	    O fb=+1
			  	   /
			  	  O fb=0    <<<< n� inserido
		
*/

void RotacaoLL(ArvAVL *raiz) { // OBS.: a "raiz" � o n� desbalanceado!!!! (fb=+-2)
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
	libera_NO(*raiz); // libera cada n�
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
	Existem 3 principais formas de percorrer uma �rvore:
	- Pr�-ordem: visita a raiz, o filho da esquerda e o filho da direita;
	- Em-ordem: visita o filho da esquerda, a raiz e o filho da direita;
	- P�s-ordem: visita o filho da esquerda, o filho da direita e a raiz; // usado nos algoritmos libera_ArvAVL, altura_ArvAVL, totalNO_ArvAVL
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
	Ap�s a insers�o padr�o:
		- calcula-se as alturas de cada sub-arvore;
		- faz-se a rota��o necess�ria cajo haja desbalanceamento;
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
struct NO* procuraMenor(struct NO* atual); // prot�tipo da fun��o

int remove_ArvAVL(ArvAVL *raiz, int valor) { // fun��o respons�vel pela busca do n� a ser removido
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
	if (valor == (*raiz)->info) { // achou n� a ser removido
		if (((*raiz)->esq == NULL || (*raiz)->dir == NULL)) { // trata se o n� a ser removido tem 1 ou nenhum filho
			struct NO *oldNode = (*raiz);
			if ((*raiz)->esq != NULL) *raiz = (*raiz)->esq;
			else *raiz = (*raiz)->dir;
			free(oldNode);
		} else { // trata caso com 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir); // busca o menor valor da sub-arvore com 'maiores' valores para substitui��o
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, temp->info); // remove o n� da substitui��o pois agora ele est� no lugar do n� removido
			if (fatorBalanceamento_NO(*raiz) >=2 ) {
				if (altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq)) RotacaoLL(raiz);
				else RotacaoLR(raiz);
			}
		}
		return 1;
	}
	
	return res;
}
struct NO* procuraMenor(struct NO* atual) { // procura o n� mais a esquerda
	struct NO *no1 = atual;
	struct NO *no2 = atual->esq;
	while(no2 != NULL) {
		no1 = no2;
		no2 = no2->esq;
	}
	return no1;
}

/*
	Consulta em uma �rvore bin�ria
		- Para um dado valor V:
			* Compara-se com a raiz;
			* Se for menor, � consultada a sub-arvore esquerda;
			* Sen�o, busca-se na sub-arvore direita;
			* � passiv�l de recurs�o, mas sem ela � mais simples;
*/
int consulta_ArvAVL(ArvAVL *raiz, int valor) { // esse m�todo retorna apenas o status (0 ou 1) se achou o n�o o valor passado
	if (raiz ==  NULL) return 0;
	struct NO* atual = *raiz;
	while (atual != NULL) {
		if (valor == atual->info) return 1;
		if (valor > atual->info) atual = atual->dir;
		else atual = atual->esq;
	}
	return 0;
}
