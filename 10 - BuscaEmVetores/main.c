#include <stdio.h>
#include <stdlib.h>
#include "BuscaEmVetores.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int vet[10] = {-8, -5, 1, 4, 14, 21, 23, 54, 67, 90};
	int x;
	
//	x = buscaLinear(vet, 10, 14);
//	x = buscaOrdenada(vet, 10, 14);
	x = buscaBinaria(vet, 10, 14);
	
	printf((x != -1) ? "OK\n" : "ERRO\n");
	printf("%d\n", x);
	
	
	struct aluno V[4] = {{2, "Andre", 9.5, 7.8, 8.5},
						{4, "Ricardo", 7.5, 8.8, 8.5},
						{1, "Bianca", 9.7, 6.5, 8.5},
						{3, "Ana", 5.7, 6.1, 8.5}};

	x = buscaLinearNome(V, 4, "Bianca");
	
	printf((x != -1) ? "OK\n" : "ERRO\n");
	printf("%d\n", x);
		
	system("pause");
	return 0;
}
