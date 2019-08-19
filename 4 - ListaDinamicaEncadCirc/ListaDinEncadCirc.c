#include <stdlib.h>
#include "ListaDinEncadCirc.h"

struct elemento {
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL) *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL && (*li) != NULL) {
        Elem *ant, *no = *li;
        while((*li) != no->prox) {
        	ant = no;
            no = no->prox;
//            *li = (*li)->prox;
            free(ant);
        }
        free(no);
        free(li);
    }
}

int tamanho_lista(Lista* li) {
    if (li == NULL || (*li) == NULL) return 0;
    int count = 0;
    Elem* no = *li;
    do {
    	count++;
    	no = no->prox;
	} while(no != (*li));
    return count;
}

int lista_vazia(Lista* li) {
    if (li == NULL || *li == NULL) return 1;
    return 0;
}

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {
    	*li = no;
    	no->prox = no;
	} else {
		Elem *aux = *li;
		while(aux->prox != (*li)) aux = aux->prox;
		aux->prox = no;
		no->prox = *li;
		*li = no; 
	}
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while(aux->prox != (*li)) aux = aux->prox;
        aux->prox = no;
        no->prox = *li;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {
        *li = no;
		no->prox = no;
        return 1;
    } else {
    	if ((*li)->dados.matricula > al.matricula) { // insere inicio
    		Elem *atual = *li;
    		while(atual->prox != (*li)) atual = atual->prox;
    		no->prox = (*li);
    		atual->prox = no;
    		*li = no;
    		return 1;
		}
        Elem *ant = *li, *atual = (*li)->prox;
        while(atual != (*li) && atual->dados.matricula < al.matricula) {
            ant = atual;
            atual = atual->prox;
        }
        ant->prox = no;
        no->prox = atual;
		
        return 1;
    }
}

//int insere_lista_ordenada2(Lista* li, struct aluno al) {
//	// ...	
//	return 1;
//}

int remove_lista_inicio(Lista* li) {
    if (li == NULL || (*li) == NULL) return 0;
    if ((*li) == (*li)->prox) {
    	free(*li);
    	*li = NULL;
    	return 1;
	}
	Elem* atual = *li;
	while (atual->prox != (*li)) atual = atual->prox;
    Elem* no = *li;
    atual->prox = no->prox;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL || (*li) == NULL) return 0;
    if ((*li) == (*li)->prox) { // só 1 elemento
    	free(*li);
    	*li = NULL;
    	return 1;
	}
    Elem *ant, *no = *li;
    while(no->prox != (*li)) { // procura o último
        ant = no;
        no = no->prox;
    }
    ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL || (*li) == NULL) return 0;
    Elem *no = *li;
    if (no->dados.matricula == mat) {
    	if (no == no->prox) {
	    	free(no);
	    	*li = NULL;
	    	return 1;
		} else {
			Elem *ult = *li;
			while(ult->prox != (*li)) ult = ult->prox;
			ult->prox = (*li)->prox;
			free(no);
			return 1;
		}
	}
	Elem *ant = no;
	no->prox;
    while(no != (*li) && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == *li) return 0;
    ant->prox = no->prox;
    free(no);
    return 1;
}

int consulta_lista_posicao(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || (*li) == NULL || pos <= 0) return 0;
    Elem *no = *li;
    int i = 1;
    while (no->prox != (*li) && i < pos) {
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
    if (li == NULL || (*li) == NULL) return 0;
    Elem *no = *li;
    while (no->prox != (*li) && no->dados.matricula != mat) no = no->prox;
    if (no->dados.matricula == mat) return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

