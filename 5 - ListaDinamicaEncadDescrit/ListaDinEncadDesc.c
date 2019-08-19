#include <stdlib.h>
#include "ListaDinEncadDesc.h"

struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

struct descritor {
	Elem *inicio;
	Elem *final;
	int qtd;
};

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) {
    	li->inicio = NULL;
    	li->final = NULL;
    	li->qtd = 0;
	}
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem *no;
        while(li->inicio != NULL) {
            no = li->inicio;
            li->inicio = li->inicio->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(Lista* li) {
    if (li == NULL ) return 0;
    return li->qtd;
}

int lista_vazia(Lista* li) {
    if (li == NULL || li->qtd == 0) return 1;
    return 0;
}

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
	no->prox = li->inicio;
	if (li->inicio == NULL) li->final = no;
	li->inicio = no;
	li->qtd++;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
	if (li->inicio == NULL) li->inicio = no;
	else li->final->prox = no;
	li->final = no;
    li->qtd++;
	return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if (li->inicio == NULL) {
        li->inicio = no;
        li->final = no;
		no->prox = NULL;
		li->qtd++;
        return 1;
    } else {
    	if (li->inicio->dados.matricula > al.matricula) { // insere inicio
			no->prox = li->inicio;
			li->inicio = no;
			li->qtd++;
    		return 1;
		}
        Elem *ant = li->inicio, *atual = li->inicio->prox;
        while(atual != NULL && atual->dados.matricula < al.matricula) {
            ant = atual;
            atual = atual->prox;
        }
        ant->prox = no;
        no->prox = atual;
        if (atual == NULL) li->final = no;
		li->qtd++;
        return 1;
    }
}

//int insere_lista_ordenada2(Lista* li, struct aluno al) {
//	// ...	
//	return 1;
//}

int remove_lista_inicio(Lista* li) {
    if (li == NULL || li->inicio == NULL) return 0;
	Elem* no = li->inicio;
	li->inicio = no->prox;
	free(no);
	if (li->inicio == NULL) li->final = NULL;
	li->qtd--;
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL || li->inicio == NULL) return 0;
    Elem *ant, *no = li->inicio;
    while(no->prox != NULL) {
        ant = no;
        no = no->prox;
    }
    if (no == li->inicio) {
    	li->inicio = NULL;
    	li->final = NULL;
	} else {
		ant->prox = no->prox; // NULL
		li->final = ant;
	}
	free(no);
	li->qtd--;
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL || li->inicio == NULL) return 0;
    Elem *no = li->inicio;
    if (no->dados.matricula == mat) {
    	li->inicio = no->prox;
		free(no);
		li->qtd--;
		return 1;
	}
	Elem *ant = no;
	no->prox;
    while(no != NULL && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == NULL) return 0;
    ant->prox = no->prox;
    if (ant->prox == NULL) li->final = ant;
    free(no);
    li->qtd--;
    return 1;
}

int consulta_lista_posicao(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0) return 0;
    if (pos == li->qtd) {
    	*al = li->final->dados;
    	return 1;
	}
    Elem *no = li->inicio;
    int i = 1;
    while (no->prox != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (i != pos) return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_matricula(Lista* li, int mat, struct aluno *al) {
    if (li == NULL || li->inicio == NULL) return 0;
    Elem *no = li->inicio;
    while (no->prox != NULL && no->dados.matricula != mat) no = no->prox;
    if (no == NULL) return 0;
    *al = no->dados;
    return 1;
}


