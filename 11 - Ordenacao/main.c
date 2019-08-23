#include <stdio.h>
#include <stdlib.h>
#include "Ordenacao.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int vet[10] = {-8, -5, 1, 4, 14, 21, 23, 54, 67, 90};
	int i;
	
//	bubbleSort(vet, 10);
//	insertionSort(vet, 10);
//	selectionSort(vet, 10);

//	mergeSort(vet, 0, 9);
//	quickSort(vet, 0, 9);
	heapSort(vet, 10);
	
	printf("Ordenado: [ ");
	for (i = 0; i < 10; i++) {
		printf("%d ", vet[i]);
	}
	printf("]\n");
	
	system("pause");
	return 0;
}
