#include <stdlib.h>
#include "BuscaEmVetores.h"

// V = vetor
// N = tamanho do vetor
// elem = elemento que busca

int buscaLinear(int *V, int N, int elem) {
	int i;
	for(i = 0; i < N; i++) {
		if (elem == V[i]) return i;
	}
	return -1;
}

int buscaOrdenada(int *V, int N, int elem) {
	int i;
	for(i = 0; i < N; i++) {
		if (elem == V[i]) return i;
		else
			if(elem < V[i]) return -1;
	}
	return -1;
}

int buscaBinaria(int *V, int N, int elem) {
	int inicio, meio, final;
	inicio = 0;
	final = N-1;
	while(inicio <=final) {
		meio = (inicio + final) / 2;
		if (elem < V[meio]) {
			final = meio - 1;
		} else {
			if (elem > V[meio]) inicio = meio + 1;
			else return meio;
		}
	}
	return -1;
}

 // ------------------------------------------
 
 int buscaLinearMatricula(struct aluno *V, int N, int mat) {
 	int i;
	for(i = 0; i < N; i++) {
		if (mat == V[i].matricula) return i;
	}
	return -1;
 }
 
int buscaLinearNome(struct aluno *V, int N, char* nome) {
 	int i;
	for(i = 0; i < N; i++) {
		if (strcmp(nome, V[i].nome) == 0) return i;
	}
	return -1;
 }
