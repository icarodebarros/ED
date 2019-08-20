#include <stdlib.h>
#include "PilhaDinamica.h"

#define MAX 100
struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Pilha* cria_pilha() {
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if (pi != NULL) *pi = NULL;
    return pi;
}

void libera_pilha(Pilha* pi) {
	if (pi != NULL) {
		Elem* no;
		while((*pi) != NULL) {
			no = *pi;
			*pi = (*pi)->prox;
			free(no);
		}
		free(pi);
	}
}

int tamanho_pilha(Pilha* pi) {
    if (pi == NULL ) return 0;
    int cont = 0;
    Elem* no = *pi;
    while(no != NULL) {
    	cont++;
    	no = no->prox;
	}
    return cont;
}

int pilha_cheia(Pilha* pi) {
	return 0;
}

int pilha_vazia(Pilha* pi) {
    if (pi == NULL || *pi == NULL) return 1;
    return 0;
}

int insere_pilha(Pilha* pi, struct aluno al) { // INSERÇÃO APENAS NO TOPO
    if (pi == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
	no->dados = al;
	no->prox = (*pi);
	*pi = no;
    return 1;
}

int remove_pilha(Pilha* pi) { // REMOÇÃO APENAS NO TOPO
    if (pi == NULL || (*pi) == NULL) return 0;
    Elem *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

int consulta_pilha(Pilha* pi, struct aluno *al) { // CONSULTA APENAS NO TOPO
    if (pi == NULL || (*pi) == NULL) return 0;
    *al = pi->dados;
    return 1;
}


