#include <stdlib.h>
#include "FilaEstatica.h"

#define MAX 100
struct fila {
    int inicio, final, qtd;
    struct aluno dados[MAX];
};

Fila* cria_fila() {
    Fila* fi = (Fila*) malloc(sizeof(Fila));
    if (fi != NULL) {
    	fi->inicio = 0;
    	fi->final = 0;
    	fi->qtd = 0;
	}
    return fi;
}

void libera_fila(Fila* fi) {
    free(fi);
}

int tamanho_fila(Fila* fi) {
    if (fi == NULL ) return -1;
    return fi->qtd;
}

int fila_cheia(Fila* fi) {
	if (fi == NULL) return -1;
	return (fi->qtd == MAX) ? 1 : 0;
}

int fila_vazia(Fila* fi) {
    if (fi == NULL) return -1;
    return (fi->qtd == 0) ? 1 : 0;
}

int insere_fila(Fila* fi, struct aluno al) { // INSERÇÃO APENAS NO FINAL
    if (fi == NULL || fila_cheia(fi)) return 0;
	fi->dados[fi->final] = al; // OBS.: o final da fila aponta para a primeira vaga livre, e não pra ulta vaga ocupada!
	fi->final = (fi->final + 1) %MAX; // a posição do final, após MAX-1 vai para o início da fila, caso este esteja livre;
	// Em outras palavras: uma fila circular!
	fi->qtd++;
    return 1;
}

int remove_fila(Fila* fi) { // REMOÇÃO APENAS NO INICIO
    if (fi == NULL || fila_vazia(fi)) return 0;
	
	fi->inicio++;
	if (fi->inicio == MAX) fi->inicio = 0;
	// OU APENAS: fi->inicio = (fi->inicio + 1) %MAX;
	
    fi->qtd--;
    return 1;
}

int consulta_fila(Fila* fi, struct aluno *al) { // CONSULTA APENAS NO INÍCIO
    if (fi == NULL || fila_vazia(fi)) return 0;
    *al = fi->dados[fi->inicio];
    return 1;
}
