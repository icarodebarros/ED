#include <stdlib.h>
#include "FilaDinamica.h"

struct fila {
    struct elemento *inicio;
    struct elemento *final;
};

struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Fila* cria_fila() {
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if (fi != NULL) {
    	fi->inicio = NULL;
    	fi->final = NULL;
	}
    return fi;
}

void libera_fila(Fila* fi) {
    if (fi != NULL) {
    	Elem* no;
    	while (fi->inicio != NULL) {
    		no = fi->inicio;
    		fi->inicio = fi->inicio->prox;
    		free(no);
		}
		free(fi);
	}
}

int tamanho_fila(Fila* fi) {
    if (fi == NULL ) return 0;
    int cont = 0;
    Elem* no = fi->inicio;
    while(no != NULL) {
    	cont++;
    	no = no->prox;
	}
    return cont;
}

int fila_cheia(Fila* fi) {
	return 0;
}

int fila_vazia(Fila* fi) {
    if (fi == NULL || fi->inicio == NULL) return 1;
    return 0;
}

int insere_fila(Fila* fi, struct aluno al) { // INSERÇÃO APENAS NO FINAL
    if (fi == NULL) return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
	if (fi->final == NULL) fi->inicio = no;
	else fi->final->prox = no;
	fi->final = no;
    return 1;
}

int remove_fila(Fila* fi) { // REMOÇÃO APENAS NO INICIO
    if (fila_vazia(fi)) return 0;
	Elem *no = fi->inicio;
	fi->inicio = fi->inicio->prox;
	if (fi->inicio == NULL) fi->final = NULL;
	free(no);
    return 1;
}

int consulta_fila(Fila* fi, struct aluno *al) { // CONSULTA APENAS NO INÍCIO
    if (fi == NULL || fila_vazia(fi)) return 0;
    *al = fi->inicio->dados;
    return 1;
}

