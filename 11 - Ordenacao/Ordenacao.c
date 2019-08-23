#include <stdlib.h>
#include "Ordenacao.h"

// V = vetor
// N = tamanho do vetor

void bubbleSort(int *V, int N) { // Melhor caso: O(N)	Pior caso: O(N^2)
	int i, continua, aux, fim = N;
	do {
		continua = 0;
		for (i = 0; i < fim - 1; i++) {
			if (V[i] > V[i+1]) {
				aux = V[i];
				V[i] = V[i+1];
				V[i+1] = aux;
				continua = 1;
			}
		}
		fim--;
	} while (continua != 0);
}
 // ------------------------------------------------------------------------------------------------
void insertionSort(int *V, int N) { // Melhor caso: O(N)	Pior caso: O(N^2)
	int i, j, aux;
	for (i = 1; i < N; i++) {
		aux = V[i];
		for(j = i; (j>0) && (aux<V[j-1]); j--) V[j] = V[j-1];
		V[j] = aux;
	}
}
// ------------------------------------------------------------------------------------------------
void selectionSort(int *V, int N) { // Melhor caso: O(N^2)	Pior caso: O(N^2)
	int i, j, menor, troca;
	for (i = 0; i < N-1; i++) {
		menor = i;
		for (j = i+1; j < N; j++) {
			if (V[j] < V[menor]) menor = j;
		}
		if(i != menor) {
			troca = V[i];
			V[i] = V[menor];
			V[menor] = troca;
		}
	}
}
// ------------------------------------------------------------------------------------------------
void mergeSort(int *V, int inicio, int fim) { // Melhor caso: O(N log N)	Pior caso: O(N log N)
	int meio;
	if (inicio < fim) {
		meio = floor((inicio+fim)/2);
		mergeSort(V, inicio, meio);
		mergeSort(V, meio+1, fim);
		merge(V, inicio, meio, fim); // combina as partes
	}
}
void merge(int *V, int inicio, int meio, int fim) {
	int *temp, p1, p2, tamanho, i, j, k;
	int fim1 = 0, fim2 = 0;
	tamanho = fim-inicio+1;
	p1 = inicio;
	p2 = meio+1;
	temp = (int*) malloc(tamanho * sizeof(int));
	if (temp != NULL) {
		for (i = 0; i < tamanho; i++) {
			if (!fim1 && !fim2) {
				if (V[p1] < V[p2]) temp[i] = V[p1++];
				else temp[i] = V[p2++];
				
				if (p1 > meio) fim1 = 1;
				if (p2 > fim) fim2 = 1;				
			} else {
				if (!fim1) temp[i] = V[p1++];
				else temp[i] = V[p2++];
			}
		}
		for (j = 0, k = inicio; j < tamanho; j++, k++) V[k] = temp[j];
	}
	free(temp);
}
// ------------------------------------------------------------------------------------------------
void quickSort(int *V, int inicio, int fim) { // Melhor caso: O(N log N)	Pior caso: O(N^2)
	int pivo;
	if (fim > inicio) {
		pivo = particiona(V, inicio, fim);
		quickSort(V, inicio, pivo - 1);
		quickSort(V, pivo + 1, fim);	
	}
}
int particiona(int *V, int inicio, int final) {
	int esq, dir, pivo, aux;
	esq = inicio;
	dir = final;
	pivo = V[inicio];
	while (esq < dir) {
		while(V[esq] <= pivo) esq++;
		while(V[dir] > pivo) dir--;
		if (esq < dir) {
			aux = V[esq];
			V[esq] = V[dir];
			V[dir] = aux;
		}		
	}
	V[inicio] = V[dir];
	V[dir] = pivo;
	return dir;
}
// ------------------------------------------------------------------------------------------------
void heapSort(int *V, int N) { // Melhor caso: O(N logN)	Pior caso: 2N logN + O(N)
	int i, aux;
	for (i = (N - 1)/2; i >= 0; i--) {
		criaHeap(V, i, N-1);
	}
	for (i = N-1; i >= 1; i--) {
		aux = V[0];
		V[0] = V[i];
		V[i] = aux;
		criaHeap(V, 0, i - 1);
	}
}
void criaHeap(int *V, int i, int f) {
	int aux = V[i];
	int j = i * 2 + 1;
	while (j <= f) {
		if (j < f) {
			if (V[j] < V[j + 1]) j++;
		}
		if (aux < V[j]) {
			V[i] = V[j];
			i = j;
			j = 2 * i + 1;
		} else {
			j = f + 1;
		}
	}
	V[i] = aux;
}
